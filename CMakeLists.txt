cmake_minimum_required(VERSION 2.8)
project(sockets)

include_directories(include)
set(SOCKETS_SOURCES 
${CMAKE_CURRENT_DIR}src/sockets.c)

set(C_FLAGS "-static")

add_library(sockets-static STATIC ${SOCKETS_SOURCES})
add_library(sockets SHARED ${SOCKETS_SOURCES})

add_executable(server ${CMAKE_CURRENT_DIR}src/server.c) #${CMAKE_CURRENT_DIR}src/sockets.c)
add_executable(client ${CMAKE_CURRENT_DIR}src/client.c) #${CMAKE_CURRENT_DIR}src/sockets.c)

link_directories(${CMAKE_CURRENT_DIR})
target_link_libraries(server sockets-static)
target_link_libraries(client sockets-static)
