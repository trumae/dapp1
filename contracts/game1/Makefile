all: compile abi

compile: game1.cpp
	eosiocpp -o game1.wast game1.cpp

abi: game1.cpp
	eosiocpp -g game1.abi game1.cpp

clean:
	rm -f *~ *.o *.wast *.abi

deploy: all
	cleos -u http://127.0.0.1:8888/ set contract game1 ../game1 -p game1
