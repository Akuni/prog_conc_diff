GCC = gcc -Wall -std=gnu99
SRC = -l src -lm 


prog: bin/main.o bin/Matrix.o bin/Matrix2D.o bin/Physics.o bin/simulator.o bin/Thread.o
	$(GCC)  bin/main.o bin/Matrix.o bin/Matrix2D.o bin/Physics.o bin/simulator.o  bin/Thread.o  -o bin/prog -lm -lpthread

bin/main.o: src/main.c
	$(GCC) -c src/main.c -o bin/main.o $(SRC)

bin/Matrix.o: src/Matrix.c src/Matrix.h
	$(GCC) -c src/Matrix.c -o bin/Matrix.o $(SRC)

bin/Matrix2D.o: src/Matrix2D.c src/Matrix2D.h
	$(GCC) -c src/Matrix2D.c -o bin/Matrix2D.o $(SRC)

bin/Physics.o: src/Physics.c src/Physics.h
	$(GCC) -c src/Physics.c -o bin/Physics.o $(SRC)

bin/simulator.o: src/simulator.c src/simulator.h
	$(GCC) -c src/simulator.c -o bin/simulator.o $(SRC)

bin/Thread.o: src/Thread.c src/Thread.h
	$(GCC) -c src/Thread.c -o bin/Thread.o $(SRC)
