all: 
	cmake -S src -B build
	cmake --build build
	./build/main
clean:
	rm -rf build/* build/.cmake