#include "graph.h"

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
	obj.djikstra("Mumbai",N);
    return 0;
}
