cmake_minimum_required(VERSION 3.8)
project(DistributedSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        starter_code/echo_client.c
        starter_code/echo_server.c
        starter_code/log.c
        starter_code/log.h
        starter_code/server.c)

add_executable(DistributedSystem ${SOURCE_FILES})