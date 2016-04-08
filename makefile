GCC = gcc -Wall -std=gnu99 -pthread
SRC = -l src

prog: bin/main.o bin/Matrix2D.o bin/Physics.o bin/simulator.o bin bin/BarrierManager.o bin/BarrierCond.o
	$(GCC)  bin/main.o bin/Matrix2D.o bin/Physics.o bin/simulator.o bin/BarrierManager.o bin/BarrierCond.o -o bin/prog

bin/main.o: src/main.c
	$(GCC) -c src/main.c -o bin/main.o $(SRC)

bin/Matrix2D.o: src/Matrix2D.c src/Matrix2D.h
	$(GCC) -c src/Matrix2D.c -o bin/Matrix2D.o $(SRC)

bin/Physics.o: src/Physics.c src/Physics.h
	$(GCC) -c src/Physics.c -o bin/Physics.o $(SRC)

bin/simulator.o: src/simulator.c src/simulator.h
	$(GCC) -c src/simulator.c -o bin/simulator.o $(SRC)

bin/BarrierManager.o: src/BarrierManager.c src/BarrierManager.h
	$(GCC) -c src/BarrierManager.c -o bin/BarrierManager.o $(SRC)

bin/BarrierCond.o: src/BarrierCond.c src/BarrierCond.h
	$(GCC) -c src/BarrierCond.c -o bin/BarrierCond.o $(SRC)