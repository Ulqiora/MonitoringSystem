GXX=g++

all:
	$(GXX) -Wall -c main.cpp
	$(GXX) main.o -ldl -o run 
	g++ -Wall -c -fPIC matrix_addition.cpp -o matrix_addition.o
	g++ -shared -Wl,-soname,libmatrix.so -o libmatrix.so matrix_addition.o
