cmake_minimum_required(VERSION 3.27)
project(uzd4prat11 C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        main.c
        bigInt.c
        bigInt.h
)