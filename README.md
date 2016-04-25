# graph_classic_cpp
Implementation of graphs in C++ (with Iterators)

-Inorder to use graph library the following prerequisites have to be met:
	-> System should have c++14 or above installed
	-> All the files in the library package should be in same folder
-Inorder to use the library:
	-> Put the library in same folder as client code
	-> inlcude "graph.h" file in the client code to use all library functionalities
-About Graph class:
	-> Can create an object by passing (1)A list of node names and (2)An adjancecy matrix i.e. vector<vector<int>>
	-> Functionalites to use are:-
		-iterator myfind(iterator first,iterator last, string val)
		-comp_graphs(iterator st1,iterator en1,iterator st2,iterator en2)
		-void djikstra(string src_, int N)
        -vector<string> topo_sort(iterator start_pt,iterator end_pt);
        -int get_number_of_components(string city);
        -And all six basic class functionalities
        
To contribute, just send pull request to : https://github.com/ksameersrk/graph_classic_cpp 
