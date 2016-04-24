graph : client.o graph.o node.o
	g++ client.o graph.o node.o -o graph
client.o : client.cpp
	g++ -std=c++14 -c client.cpp graph.h
graph.o : graph.cpp
	g++ -std=c++14 -c graph.cpp graph.h
node.o : node.cpp
	g++ -std=c++14 -c node.cpp node.h

