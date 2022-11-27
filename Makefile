all: ready compile assemble run

# generate src/ and out/ if they don't exist
ready:
	mkdir -p src out

# Compile the source code
compile: src/main.cpp src/operations.cpp src/operations.h
	gcc -c -o out/main.o src/main.cpp
	gcc -c -o out/operations.o src/operations.cpp

# Assemble the object files
assemble: out/main.o out/operations.o
	g++ out/main.o out/operations.o -o out/prog

run: out/prog
	echo "The program is run with the following command: "
	echo "./out/prog <array_length> <number_of_threads>"
	echo "Running for 100000 elements and 10 threads"
	./out/prog 100000 10
