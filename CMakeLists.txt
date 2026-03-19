cmake_minimum_required(VERSION 3.10)
project(sockets C)

# Enforce C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

# ---------------------------------------------------------------------------
# Legacy socket library (sockets.c / compat.c)
# ---------------------------------------------------------------------------
set(SOCKETS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compat.c)

add_library(sockets-static STATIC ${SOCKETS_SOURCES})
add_library(sockets        SHARED ${SOCKETS_SOURCES})

foreach(_target sockets-static sockets)
    target_include_directories(${_target} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
endforeach()

add_executable(server ${CMAKE_CURRENT_SOURCE_DIR}/src/server.c)
add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/src/client.c)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(server sockets-static)
target_link_libraries(client sockets-static)

# ---------------------------------------------------------------------------
# libuv-based async socket library
# ---------------------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUV REQUIRED libuv)

set(UV_SOCKETS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/uv_sockets.c)

add_library(uv_sockets-static STATIC ${UV_SOCKETS_SOURCES})
add_library(uv_sockets        SHARED ${UV_SOCKETS_SOURCES})

foreach(_target uv_sockets-static uv_sockets)
    target_include_directories(${_target} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIBUV_INCLUDE_DIRS})
    target_link_libraries(${_target} ${LIBUV_LIBRARIES})
endforeach()

add_executable(uv_server ${CMAKE_CURRENT_SOURCE_DIR}/src/uv_server.c)
add_executable(uv_client ${CMAKE_CURRENT_SOURCE_DIR}/src/uv_client.c)

target_include_directories(uv_server PRIVATE ${LIBUV_INCLUDE_DIRS})
target_include_directories(uv_client PRIVATE ${LIBUV_INCLUDE_DIRS})
target_link_libraries(uv_server uv_sockets-static)
target_link_libraries(uv_client uv_sockets-static)
