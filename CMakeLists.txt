cmake_minimum_required(VERSION 3.3)
project(prog_conc_diff)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99 -pthread")


set(SOURCE_FILES src/main.c src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h src/simulator.h src/simulator.c src/BarrierManager.c src/BarrierManager.h src/BarrierCond.c src/BarrierCond.h)
add_executable(prog_conc_diff ${SOURCE_FILES} src/Physics.c src/Physics.h src/Matrix2D.c src/Matrix2D.h)
target_link_libraries(prog_conc_diff pthread)
