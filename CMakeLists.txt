cmake_minimum_required(VERSION 3.3)
project(prog_conc_diff)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c Matrix.c Matrix.h Physics.c Physics.h Matrix2D.c Matrix2D.h)
add_executable(prog_conc_diff ${SOURCE_FILES} Matrix.c Matrix.h Physics.c Physics.h Matrix2D.c Matrix2D.h)