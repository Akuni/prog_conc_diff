cmake_minimum_required(VERSION 3.3)
project(prog_conc_diff)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

set(SOURCE_FILES src/main.c src/Matrix.c src/Matrix.h src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h src/simulator.h src/simulator.c)
add_executable(prog_conc_diff ${SOURCE_FILES} src/Matrix.c src/Matrix.h src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h)