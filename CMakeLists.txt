project(sockets)
cmake_minimum_required(VERSION 2.8)

set(SOCKETS_SOURCES structs.c sockets.c)
add_executable(server server.c ${SOCKETS_SOURCES})
add_executable(client client.c ${SOCKETS_SOURCES})
add_library(graphics_static sockets.c)
add_library(graphics SHARED sockets.c)
