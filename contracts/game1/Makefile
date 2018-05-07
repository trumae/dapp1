all: compile abi

compile: game1.cpp
	eosiocpp -o game1.wast game1.cpp

abi: game1.cpp
	eosiocpp -g game1.abi game1.cpp

clean:
	rm -f *~ *.o *.wast *.abi
