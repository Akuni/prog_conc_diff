cmake_minimum_required(VERSION 3.3)
project(prog_conc_diff)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99 -lpthread -lm")
set(SOURCE_FILES src/main.c src/Matrix.c src/Matrix.h src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h src/simulator.h src/simulator.c src/Thread.c src/Thread.h)
add_executable(prog_conc_diff ${SOURCE_FILES} src/Matrix.c src/Matrix.h src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h src/Thread.c src/Thread.h)
target_link_libraries(prog_conc_diff pthread)
target_link_libraries(prog_conc_diff m)