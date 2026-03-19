sockets
=======

Sockets is a simple library for UDP/TCP sockets, with IPV4 or IPV6.

## libuv Integration

The library now ships a second, modern API built on top of
[libuv](https://libuv.org/) that provides fully **asynchronous, non-blocking**
TCP communication via a callback-driven event loop.

### Build requirements

- CMake ≥ 3.10
- A C11-capable compiler (GCC, Clang, …)
- libuv ≥ 1.0 development headers (`libuv1-dev` on Debian/Ubuntu)

### Building

```sh
mkdir build && cd build
cmake ..
make
```

This produces:

| Target | Description |
|---|---|
| `libsockets-static.a` / `libsockets.so` | Legacy blocking socket library |
| `libuv_sockets-static.a` / `libuv_sockets.so` | Async libuv-based socket library |
| `server` / `client` | Legacy example programs |
| `uv_server` / `uv_client` | Async libuv example programs |

### libuv API overview

Include `uv_sockets.h` and link against `libuv_sockets`.

#### Server

```c
uvsock_server_t server;
uvsock_server_init(&server, NULL);          // NULL → default loop
uvsock_server_bind(&server, NULL, 8080);    // NULL host → all interfaces
uvsock_server_listen(&server, 128, on_connection);
uvsock_run(NULL);
```

#### Client

```c
uvsock_client_t client;
uvsock_client_init(&client, NULL);
uvsock_client_connect(&client, "127.0.0.1", 8080, on_connect);
uvsock_run(NULL);
```

#### Callbacks

```c
// New inbound connection
void on_connection(uvsock_server_t *srv, uvsock_client_t *client, int status);

// Outbound connection result
void on_connect(uvsock_client_t *client, int status);

// Data received
void on_read(uvsock_client_t *client, const char *data, ssize_t length);

// Write complete
void on_write(uvsock_client_t *client, int status);
```

See `src/uv_server.c` and `src/uv_client.c` for complete working examples.
