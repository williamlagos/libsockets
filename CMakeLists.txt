project(sockets)
cmake_minimum_required(VERSION 2.8)

set(SOCKETS_SOURCES structs.c sockets.c)
set(SOCKETS_HEADERS structs.h sockets.h utils.h) 
add_executable(server server.c ${SOCKETS_SOURCES} ${SOCKETS_HEADERS})
add_executable(client client.c ${SOCKETS_SOURCES} ${SOCKETS_HEADERS})
add_library(sockets_static sockets.c ${SOCKETS_HEADERS})
add_library(sockets SHARED sockets.c ${SOCKETS_HEADERS})
