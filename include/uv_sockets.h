/**
 * uv_sockets.h - Async socket API built on libuv
 *
 * Provides a callback-driven TCP/UDP interface over libuv's event loop,
 * offering non-blocking I/O for both IPv4 and IPv6.
 */
#ifndef UV_SOCKETS_H
#define UV_SOCKETS_H

#include <uv.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Forward declarations
 * ---------------------------------------------------------------------- */

typedef struct uvsock_server_s  uvsock_server_t;
typedef struct uvsock_client_s  uvsock_client_t;
typedef struct uvsock_write_s   uvsock_write_t;

/* -------------------------------------------------------------------------
 * Callback types
 * ---------------------------------------------------------------------- */

/**
 * Called when a new inbound connection is accepted.
 *
 * The callback takes **ownership** of @p client: it must eventually call
 * uvsock_client_close() (and free the memory in its close callback), or free
 * the pointer directly if the connection is refused immediately.
 *
 * @param server  The listening server.
 * @param client  Newly-accepted client handle (NULL on error).
 * @param status  0 on success, libuv error code on failure.
 */
typedef void (*uvsock_connection_cb)(uvsock_server_t *server,
                                     uvsock_client_t *client,
                                     int status);

/**
 * Called when an outbound TCP connection completes.
 * @param client  The connecting client.
 * @param status  0 on success, libuv error code on failure.
 */
typedef void (*uvsock_connect_cb)(uvsock_client_t *client, int status);

/**
 * Called when data arrives on a client handle.
 * @param client  Source client.
 * @param data    Pointer to received data (NULL signals EOF/error).
 * @param length  Number of bytes received (0 on EOF; negative on error).
 */
typedef void (*uvsock_read_cb)(uvsock_client_t *client,
                               const char *data,
                               ssize_t length);

/**
 * Called after a write operation completes.
 * @param client  Target client.
 * @param status  0 on success, libuv error code on failure.
 */
typedef void (*uvsock_write_cb)(uvsock_client_t *client, int status);

/**
 * Called when a client handle is fully closed.
 * @param client  The now-closed client.
 */
typedef void (*uvsock_close_cb)(uvsock_client_t *client);

/* -------------------------------------------------------------------------
 * uvsock_server_t  —  TCP listening server
 * ---------------------------------------------------------------------- */

struct uvsock_server_s {
    uv_tcp_t          handle;        /**< libuv TCP handle. */
    uv_loop_t        *loop;          /**< Event loop. */
    uvsock_connection_cb on_connection; /**< New-connection callback. */
    void             *data;          /**< User-supplied context pointer. */
};

/* -------------------------------------------------------------------------
 * uvsock_client_t  —  Connected TCP peer (inbound or outbound)
 * ---------------------------------------------------------------------- */

struct uvsock_client_s {
    uv_tcp_t          handle;        /**< libuv TCP handle. */
    uv_loop_t        *loop;          /**< Event loop. */
    uvsock_read_cb    on_read;       /**< Data-received callback. */
    uvsock_close_cb   on_close;      /**< Close-complete callback. */
    void             *data;          /**< User-supplied context pointer. */
};

/* -------------------------------------------------------------------------
 * Write request helper (allocated per uvsock_write call)
 * ---------------------------------------------------------------------- */

struct uvsock_write_s {
    uv_write_t        req;           /**< libuv write request. */
    uv_buf_t          buf;           /**< Buffer sent. */
    uvsock_client_t  *client;        /**< Owning client. */
    uvsock_write_cb   on_write;      /**< Completion callback. */
};

/* -------------------------------------------------------------------------
 * Server API
 * ---------------------------------------------------------------------- */

/**
 * Initialise a server on the given event loop.
 *
 * @param server  Pre-allocated server struct to initialise.
 * @param loop    Event loop to attach to (NULL → default loop).
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_server_init(uvsock_server_t *server, uv_loop_t *loop);

/**
 * Bind the server to a local address.
 *
 * @param server  Initialised server.
 * @param host    Hostname or IP string; NULL or "" binds to all interfaces.
 * @param port    Port number (host byte order).
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_server_bind(uvsock_server_t *server, const char *host,
                       uint16_t port);

/**
 * Start accepting inbound connections.
 *
 * @param server   Bound server.
 * @param backlog  Listen queue depth.
 * @param cb       Callback invoked for each new connection.
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_server_listen(uvsock_server_t *server, int backlog,
                         uvsock_connection_cb cb);

/**
 * Stop accepting new connections and close the server handle.
 *
 * @param server  Running server.
 */
void uvsock_server_close(uvsock_server_t *server);

/* -------------------------------------------------------------------------
 * Client API
 * ---------------------------------------------------------------------- */

/**
 * Initialise a client on the given event loop.
 *
 * @param client  Pre-allocated client struct to initialise.
 * @param loop    Event loop to attach to (NULL → default loop).
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_client_init(uvsock_client_t *client, uv_loop_t *loop);

/**
 * Establish an outbound TCP connection.
 *
 * @param client  Initialised client.
 * @param host    Remote hostname or IP string.
 * @param port    Remote port (host byte order).
 * @param cb      Callback invoked when the connection succeeds or fails.
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_client_connect(uvsock_client_t *client, const char *host,
                          uint16_t port, uvsock_connect_cb cb);

/**
 * Begin receiving data on a connected client handle.
 *
 * @param client  Connected client.
 * @param cb      Callback invoked when data arrives.
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_read_start(uvsock_client_t *client, uvsock_read_cb cb);

/**
 * Stop receiving data on a client handle.
 *
 * @param client  Reading client.
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_read_stop(uvsock_client_t *client);

/**
 * Send data over a connected client handle.
 *
 * @param client  Target client.
 * @param data    Buffer to send.
 * @param length  Number of bytes to send.
 * @param cb      Completion callback (may be NULL).
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_write(uvsock_client_t *client, const char *data, size_t length,
                 uvsock_write_cb cb);

/**
 * Close a client handle and free libuv resources.
 *
 * @param client  Client to close.
 * @param cb      Called when the handle is fully closed (may be NULL).
 */
void uvsock_client_close(uvsock_client_t *client, uvsock_close_cb cb);

/* -------------------------------------------------------------------------
 * Event-loop helpers
 * ---------------------------------------------------------------------- */

/**
 * Run the event loop until all handles and requests are done.
 *
 * @param loop  Event loop (NULL → default loop).
 * @return 0 on success, libuv error code on failure.
 */
int uvsock_run(uv_loop_t *loop);

/**
 * Return the default libuv event loop.
 */
uv_loop_t *uvsock_default_loop(void);

#ifdef __cplusplus
}
#endif

#endif /* UV_SOCKETS_H */
