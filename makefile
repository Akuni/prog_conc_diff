GCC = gcc -Wall -std=c99

ALL = bin/prog

bin/prog: src/main.o src/Matrix.o src/Matrix2D.o src/Physics.o src/Simulator.o
	$(GCC) -o bin/main bin/main.o bin/Matrix.o bin/Matrix2D.o bin/Physics.o bin/Simulator.o

bin/main.o: src/main.c
	$(GCC) -c src/main.c bin/main.o

bin/Matrix.o: src/Matrix.c src/Matrix.h
	$(GCC) -c src/Matrix.c bin/Matrix.o

bin/Matrix2D.o: src/Matrix2D.c src/Matrix2D.h
	$(GCC) -c src/Matrix2D.c bin/Matrix2D.o

bin/Physics.o: src/Physics.c src/Physics.h
	$(GCC) -c src/Physics.c bin/Physics.o

bin/Simulator.o: src/Simulator.c src/Simulator.h
	$(GCC) -c src/Simulator.c bin/Simulator.o