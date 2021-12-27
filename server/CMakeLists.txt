cmake_minimum_required(VERSION 3.0)

project(netradio)

include_directories(../inc)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES
    server.cpp
    Channel.cpp
)


add_executable(netradio ${SOURCES})

target_link_libraries(netradio PRIVATE Threads::Threads)