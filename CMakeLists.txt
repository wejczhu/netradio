cmake_minimum_required(VERSION 3.0)

project(netradio)

include_directories(inc)

set(SOURCES
    main.cpp
    src/test.cpp
)


add_executable(netradio ${SOURCES})