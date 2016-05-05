GCC = gcc -Wall -std=gnu99
SRC = -l src -lm

all: dir prog


dir :
	@echo "Creating bin folder ..."
	-@mkdir -p bin/
	@echo "Folder created"
prog: bin/main.o bin/Barrier.o bin/Matrix2D.o bin/Physics.o bin/Simulator.o bin/Thread.o bin/Semaphore.o
	$(GCC)  bin/main.o bin/Barrier.o bin/Matrix2D.o bin/Physics.o bin/Simulator.o bin/Semaphore.o bin/Thread.o  -o bin/prog -lm -lpthread
	@echo "Compilation done !"

bin/main.o: src/main.c
	@echo "Compiling ..."
	$(GCC) -c src/main.c -o bin/main.o $(SRC)

bin/Barrier.o: src/Barrier.c src/Barrier.h
	$(GCC) -c src/Barrier.c -o bin/Barrier.o $(SRC)

bin/Matrix2D.o: src/Matrix2D.c src/Matrix2D.h
	$(GCC) -c src/Matrix2D.c -o bin/Matrix2D.o $(SRC)

bin/Physics.o: src/Physics.c src/Physics.h
	$(GCC) -c src/Physics.c -o bin/Physics.o $(SRC)

bin/Simulator.o: src/Simulator.c src/Simulator.h
	$(GCC) -c src/Simulator.c -o bin/Simulator.o $(SRC)

bin/Thread.o: src/Thread.c src/Thread.h
	$(GCC) -c src/Thread.c -o bin/Thread.o $(SRC)

bin/Semaphore.o: src/Semaphore.c src/Semaphore.h
	$(GCC) -c src/Semaphore.c -o bin/Semaphore.o $(SRC)

clean:
	@echo "Removing files ..."
	-@rm -f bin/* 2>/dev/null || true
	@echo "Clean done"
