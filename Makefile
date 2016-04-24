graph : client.o graph.o
	g++ client.o graph.o node.o -o graph
client.o : client.cpp graph.h
	g++ -std=c++14 -c client.cpp
graph.o : graph.cpp
	g++ -std=c++14 -c graph.cpp
node.o : node.cpp
	g++ -std=c++14 -c node.cpp

