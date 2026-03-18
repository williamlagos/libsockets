/**
 * uv_client.c - Echo client example using the libuv-based socket API.
 *
 * Usage:  uv_client <host> <port>
 *
 * Connects to the echo server, sends a greeting, prints the echoed reply,
 * then closes the connection.
 */
#include "uv_sockets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------
 * Callbacks
 * ---------------------------------------------------------------------- */

static void on_close(uvsock_client_t *client)
{
    printf("[client] connection closed\n");
    (void)client;
}

static void on_read(uvsock_client_t *client, const char *data, ssize_t length)
{
    if (length <= 0) {
        if (length < 0)
            fprintf(stderr, "[client] read error: %s\n",
                    uv_strerror((int)length));
        uvsock_client_close(client, on_close);
        return;
    }

    printf("[client] received: %.*s\n", (int)length, data);
    /* Close after first echo reply. */
    uvsock_read_stop(client);
    uvsock_client_close(client, on_close);
}

static void on_write(uvsock_client_t *client, int status)
{
    if (status != 0) {
        fprintf(stderr, "[client] write error: %s\n", uv_strerror(status));
        uvsock_client_close(client, on_close);
        return;
    }
    /* Start reading the echo reply now that the write is confirmed. */
    uvsock_read_start(client, on_read);
}

static void on_connect(uvsock_client_t *client, int status)
{
    static const char msg[] = "Hello from uv_client!\n";

    if (status != 0) {
        fprintf(stderr, "[client] connect error: %s\n", uv_strerror(status));
        uvsock_client_close(client, on_close);
        return;
    }

    printf("[client] connected\n");
    uvsock_write(client, msg, strlen(msg), on_write);
}

/* -------------------------------------------------------------------------
 * Entry point
 * ---------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    uvsock_client_t client;
    uint16_t port;
    int err;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return 1;
    }

    port = (uint16_t)atoi(argv[2]);

    err = uvsock_client_init(&client, NULL);
    if (err != 0) {
        fprintf(stderr, "uvsock_client_init: %s\n", uv_strerror(err));
        return 1;
    }

    err = uvsock_client_connect(&client, argv[1], port, on_connect);
    if (err != 0) {
        fprintf(stderr, "uvsock_client_connect: %s\n", uv_strerror(err));
        return 1;
    }

    return uvsock_run(NULL);
}
