cmake_minimum_required(VERSION 3.0)

project(client)

include_directories(../inc)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES
    client.cpp
)


add_executable(client ${SOURCES})

target_link_libraries(client PRIVATE Threads::Threads)