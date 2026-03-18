/**
 * uv_server.c - Echo server example using the libuv-based socket API.
 *
 * Usage:  uv_server <port>
 *
 * Accepts TCP connections on the given port and echoes back any data
 * received from each client. Closes a client connection on EOF.
 */
#include "uv_sockets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------
 * Callbacks
 * ---------------------------------------------------------------------- */

static void on_client_close(uvsock_client_t *client)
{
    printf("[server] client closed\n");
    free(client);
}

static void on_write(uvsock_client_t *client, int status)
{
    if (status != 0)
        fprintf(stderr, "[server] write error: %s\n", uv_strerror(status));
    (void)client;
}

static void on_read(uvsock_client_t *client, const char *data, ssize_t length)
{
    if (length <= 0) {
        /* EOF or error – close this client. */
        if (length < 0)
            fprintf(stderr, "[server] read error: %s\n",
                    uv_strerror((int)length));
        uvsock_client_close(client, on_client_close);
        return;
    }

    /* Echo the data back. */
    uvsock_write(client, data, (size_t)length, on_write);
}

static void on_connection(uvsock_server_t *server, uvsock_client_t *client,
                          int status)
{
    (void)server;

    if (status != 0 || !client) {
        fprintf(stderr, "[server] connection error: %s\n",
                uv_strerror(status));
        return;
    }

    printf("[server] new client connected\n");
    uvsock_read_start(client, on_read);
}

/* -------------------------------------------------------------------------
 * Entry point
 * ---------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    uvsock_server_t server;
    uint16_t port;
    int err;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    port = (uint16_t)atoi(argv[1]);

    err = uvsock_server_init(&server, NULL);
    if (err != 0) {
        fprintf(stderr, "uvsock_server_init: %s\n", uv_strerror(err));
        return 1;
    }

    err = uvsock_server_bind(&server, NULL, port);
    if (err != 0) {
        fprintf(stderr, "uvsock_server_bind: %s\n", uv_strerror(err));
        return 1;
    }

    err = uvsock_server_listen(&server, 128, on_connection);
    if (err != 0) {
        fprintf(stderr, "uvsock_server_listen: %s\n", uv_strerror(err));
        return 1;
    }

    printf("[server] listening on port %u\n", port);
    return uvsock_run(NULL);
}
