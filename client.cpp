#include "graph.h"
#include "limits.h"

vector<vector<int>> input_matrix(int N)
{
    vector<vector<int>> v; 
    for(int i=0; i<N; i++)
    {
        vector<int> tmp;
        for(int j=0; j<N; j++)
        {
            int value;
            cin >> value;
            tmp.push_back(value);
        }
        v.push_back(tmp);
    }
    return v;
}

vector<string> input_string(int N)
{
    vector<string> v;
    string ch;
    for(int i=0; i<N; i++)
    {
        ch = new char[100];
        cin >> ch;
        v.push_back(ch);
    }
    return v;
}

template<typename ptr>
void disp(ptr first, ptr last)
{
    while(first != last)
    {
        cout << *first << "   ";
        ++first;
    }
    cout << endl << endl;
}

template<typename ptr>
void disp2(ptr first, ptr last)
{
    while(first != last)
    {
        cout << *first << "   ";
        first++;
    }
    cout << endl << endl;
}

void djikstra(string src, Graph g)
{
    
    int N = g.get_size();  //to get size of graph
    int matrix[N][N];
    for(int i=0; i<N; i++)
	{
	    for(int j=0; j<N; j++)
	    {
	        matrix[i][j] = 0;
	    }
	}
	int src_ = g.get_index(src);    //to get index of source
	int distances[N];
	bool shortest_path_set[N];
	for(int i=0; i<N; i++)
	{
		distances[i] = INT_MAX;
		shortest_path_set[i] = false;		
	}
	distances[src_] = 0;
	int min_v;
	for(int i=0; i<N; i++)
	{
		int min = INT_MAX;
		min_v = -1;
		for(int i=0; i<N; i++)
		{
			if(distances[i] < min && shortest_path_set[i] == false)
			{
				min_v = i;
				min = distances[i];
			}
		}	
		shortest_path_set[min_v] = true;
		//update dists of all nbrs of min_v
		for(auto k : g.get_neighbours(min_v))   //to get neighbour vector of src
		{
			if(shortest_path_set[k.first]==false && distances[min_v]!=INT_MAX 
				&& distances[k.first] > distances[min_v]+k.second)
			{
				distances[k.first] = distances[min_v]+k.second;
				matrix[min_v][k.first] = distances[k.first];
			}
		}
	}
	for(int i=0; i<N; i++)
	{
		cout << g.get_value(src_) << " To " << g.get_value(i) << " --> " << distances[i] << "\n";
		//to get name of nodes
	}
	
	cout << "\n";
}

int main()
{
    int N;
    cin >> N;
    vector<string> vertex_names = input_string(N);
    vector<vector<int>> adjacency_matrix = input_matrix(N);
    
    Graph g(adjacency_matrix, vertex_names);
    cout << "Created graph object g" << endl;
    
    Graph h(g);
    cout << "Copy constructor h<-g" << endl;
    
    Graph i(move(h));
    cout << "Move constructor i<-h" << endl;
    
    Graph j = i;
    cout << "Copy Assignment j<-i" << endl;
    
    Graph k = move(j);
    cout << "Move assignment k<-j" << endl << endl;

    
    cout << "BFS : Belgaum -> Chennai : ";
    disp(g.begin_bfs("Belgaum"), g.end_bfs("Chennai"));
    
    cout << "DFS : Chennai -> *No destination : ";
    disp(g.begin_dfs("Chennai"), g.end_dfs());
    
    cout << "Topo sort : Belgaum -> Chennai : ";   
    vector<string> test= g.topo_sort(g.begin_dfs("Belgaum"), g.end_dfs("Chennai"));
    disp(test.begin(), test.end());
    
    cout << "Number of components : " << g.get_number_of_components("Mumbai") << endl << endl; 
    
    cout << "Compare graph : (g('Belgaum') == i('Belgaum') -> " << comp_graphs(g.begin_dfs("Belgaum"), 
                                                          g.end_dfs(),
                                                          g.begin_dfs("Belgaum"),
                                                          g.end_dfs()
                                                         ) << endl ;

    cout << "Compare graph : (g('Belgaum') == i('Bangalore') -> " << comp_graphs(g.begin_dfs("Belgaum"), 
                                                          g.end_dfs(),
                                                          g.begin_dfs("Bangalore"),
                                                          g.end_dfs()
                                                         ) << endl << endl ;
   
    cout << "Dijkstra matrix " << endl;
    cin >> N;
    vertex_names = input_string(N);
    adjacency_matrix = input_matrix(N);
    Graph obj(adjacency_matrix, vertex_names);
	djikstra("Mumbai", obj);
	
    return 0;
}
