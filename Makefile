all: 
	cmake -S src -B build
	cmake --build build --target=AgentCPU
	cmake --build build --target=myapp
	./build/myapp /home/ccnc/Desktop/MonitoringSystem/build/DLL/AgentCPU/libAgentCPU.so
clean:
	rm -rf build/* build/.cmake