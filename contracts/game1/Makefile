all: compile abi

compile:
	eosiocpp -o game1.wast game1.cpp

abi:
	eosiocpp -g game1.abi game1.cpp

clean:
	rm -f *~ *.o *.wast *.abi
