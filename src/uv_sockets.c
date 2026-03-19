/**
 * uv_sockets.c - Async socket implementation built on libuv
 */
#include "uv_sockets.h"

#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------
 * Internal libuv callback prototypes
 * ---------------------------------------------------------------------- */

static void on_new_connection(uv_stream_t *srv, int status);
static void alloc_buffer(uv_handle_t *handle, size_t suggested_size,
                         uv_buf_t *buf);
static void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
static void on_write_done(uv_write_t *req, int status);
static void on_close_done(uv_handle_t *handle);
static void on_connect_done(uv_connect_t *req, int status);

/* -------------------------------------------------------------------------
 * Internal connect request (stack-allocated per uvsock_client_connect call)
 * ---------------------------------------------------------------------- */

typedef struct {
    uv_connect_t      req;
    uvsock_client_t  *client;
    uvsock_connect_cb cb;
} connect_req_t;

/* -------------------------------------------------------------------------
 * Server API
 * ---------------------------------------------------------------------- */

int
uvsock_server_init(uvsock_server_t *server, uv_loop_t *loop)
{
    if (!server) return UV_EINVAL;
    if (!loop) loop = uv_default_loop();

    memset(server, 0, sizeof(*server));
    server->loop = loop;
    return uv_tcp_init(loop, &server->handle);
}

int
uvsock_server_bind(uvsock_server_t *server, const char *host, uint16_t port)
{
    struct sockaddr_storage addr;
    int err;

    if (!server) return UV_EINVAL;

    /* Try IPv4 first, fall back to IPv6. */
    err = uv_ip4_addr(host && *host ? host : "0.0.0.0", port,
                      (struct sockaddr_in *)&addr);
    if (err != 0) {
        err = uv_ip6_addr(host && *host ? host : "::", port,
                          (struct sockaddr_in6 *)&addr);
        if (err != 0) return err;
    }

    return uv_tcp_bind(&server->handle, (const struct sockaddr *)&addr, 0);
}

int
uvsock_server_listen(uvsock_server_t *server, int backlog,
                     uvsock_connection_cb cb)
{
    if (!server || !cb) return UV_EINVAL;
    server->on_connection = cb;
    server->handle.data   = server;
    return uv_listen((uv_stream_t *)&server->handle, backlog,
                     on_new_connection);
}

void
uvsock_server_close(uvsock_server_t *server)
{
    if (!server) return;
    if (!uv_is_closing((uv_handle_t *)&server->handle))
        uv_close((uv_handle_t *)&server->handle, NULL);
}

/* -------------------------------------------------------------------------
 * Client API
 * ---------------------------------------------------------------------- */

int
uvsock_client_init(uvsock_client_t *client, uv_loop_t *loop)
{
    if (!client) return UV_EINVAL;
    if (!loop) loop = uv_default_loop();

    memset(client, 0, sizeof(*client));
    client->loop = loop;
    return uv_tcp_init(loop, &client->handle);
}

int
uvsock_client_connect(uvsock_client_t *client, const char *host,
                      uint16_t port, uvsock_connect_cb cb)
{
    struct sockaddr_storage addr;
    connect_req_t *req;
    int err;

    if (!client || !host || !cb) return UV_EINVAL;

    /* Try IPv4 first, fall back to IPv6. */
    err = uv_ip4_addr(host, port, (struct sockaddr_in *)&addr);
    if (err != 0) {
        err = uv_ip6_addr(host, port, (struct sockaddr_in6 *)&addr);
        if (err != 0) return err;
    }

    req = (connect_req_t *)malloc(sizeof(*req));
    if (!req) return UV_ENOMEM;

    req->client = client;
    req->cb     = cb;

    client->handle.data = client;

    err = uv_tcp_connect(&req->req, &client->handle,
                         (const struct sockaddr *)&addr,
                         on_connect_done);
    if (err != 0) {
        free(req);
        return err;
    }

    req->req.data = req;
    return 0;
}

int
uvsock_read_start(uvsock_client_t *client, uvsock_read_cb cb)
{
    if (!client || !cb) return UV_EINVAL;
    client->on_read      = cb;
    client->handle.data  = client;
    return uv_read_start((uv_stream_t *)&client->handle, alloc_buffer,
                         on_read);
}

int
uvsock_read_stop(uvsock_client_t *client)
{
    if (!client) return UV_EINVAL;
    return uv_read_stop((uv_stream_t *)&client->handle);
}

int
uvsock_write(uvsock_client_t *client, const char *data, size_t length,
             uvsock_write_cb cb)
{
    uvsock_write_t *wr;
    char *buf_copy;
    int err;

    if (!client || !data || length == 0) return UV_EINVAL;

    wr = (uvsock_write_t *)malloc(sizeof(*wr));
    if (!wr) return UV_ENOMEM;

    buf_copy = (char *)malloc(length);
    if (!buf_copy) {
        free(wr);
        return UV_ENOMEM;
    }
    memcpy(buf_copy, data, length);

    wr->buf      = uv_buf_init(buf_copy, (unsigned int)length);
    wr->client   = client;
    wr->on_write = cb;
    wr->req.data = wr;

    err = uv_write(&wr->req, (uv_stream_t *)&client->handle, &wr->buf, 1,
                   on_write_done);
    if (err != 0) {
        free(buf_copy);
        free(wr);
    }
    return err;
}

void
uvsock_client_close(uvsock_client_t *client, uvsock_close_cb cb)
{
    if (!client) return;
    client->on_close = cb;
    if (!uv_is_closing((uv_handle_t *)&client->handle))
        uv_close((uv_handle_t *)&client->handle, on_close_done);
}

/* -------------------------------------------------------------------------
 * Event-loop helpers
 * ---------------------------------------------------------------------- */

int
uvsock_run(uv_loop_t *loop)
{
    if (!loop) loop = uv_default_loop();
    return uv_run(loop, UV_RUN_DEFAULT);
}

uv_loop_t *
uvsock_default_loop(void)
{
    return uv_default_loop();
}

/* -------------------------------------------------------------------------
 * Internal libuv callbacks
 * ---------------------------------------------------------------------- */

static void
on_new_connection(uv_stream_t *srv, int status)
{
    uvsock_server_t *server = (uvsock_server_t *)srv->data;
    uvsock_client_t *client;
    int err;

    if (status < 0) {
        if (server->on_connection)
            server->on_connection(server, NULL, status);
        return;
    }

    client = (uvsock_client_t *)malloc(sizeof(*client));
    if (!client) {
        if (server->on_connection)
            server->on_connection(server, NULL, UV_ENOMEM);
        return;
    }

    err = uvsock_client_init(client, server->loop);
    if (err != 0) {
        free(client);
        if (server->on_connection)
            server->on_connection(server, NULL, err);
        return;
    }

    err = uv_accept(srv, (uv_stream_t *)&client->handle);
    if (err != 0) {
        uvsock_client_close(client, NULL);
        if (server->on_connection)
            server->on_connection(server, NULL, err);
        return;
    }

    client->handle.data = client;

    if (server->on_connection)
        server->on_connection(server, client, 0);
}

static void
alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    uvsock_client_t *client = (uvsock_client_t *)handle->data;

    buf->base = (char *)malloc(suggested_size);
    if (!buf->base) {
        buf->len = 0;
        /* Close the client if we cannot allocate a read buffer. */
        uvsock_client_close(client, client->on_close);
        return;
    }
    buf->len = (unsigned int)suggested_size;
}

static void
on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    uvsock_client_t *client = (uvsock_client_t *)stream->data;

    if (nread > 0) {
        if (client->on_read)
            client->on_read(client, buf->base, nread);
    } else if (nread == UV_EOF) {
        if (client->on_read)
            client->on_read(client, NULL, 0);
    } else if (nread < 0) {
        if (client->on_read)
            client->on_read(client, NULL, nread);
    }

    if (buf->base)
        free(buf->base);
}

static void
on_write_done(uv_write_t *req, int status)
{
    uvsock_write_t *wr = (uvsock_write_t *)req->data;

    if (wr->on_write)
        wr->on_write(wr->client, status);

    free(wr->buf.base);
    free(wr);
}

static void
on_close_done(uv_handle_t *handle)
{
    uvsock_client_t *client = (uvsock_client_t *)handle->data;

    if (client && client->on_close)
        client->on_close(client);
}

static void
on_connect_done(uv_connect_t *req, int status)
{
    connect_req_t   *cr     = (connect_req_t *)req->data;
    uvsock_client_t *client = cr->client;
    uvsock_connect_cb cb    = cr->cb;

    free(cr);

    if (cb) cb(client, status);
}
