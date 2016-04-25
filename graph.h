#include "node.h"

class Graph
{
    private:
        vector<Node> graph_;
        vector<string> node_names_;
        map<string, int> name_index_;
        Node dummy_node;
        
    public:
        //default ctor
        Graph();
        //constructor
        Graph(const vector<vector<int>>& matrix,
                vector<string> node_names);      
        //destructor
        ~Graph();        
        //copy constructor
        Graph(const Graph& rhs);        
        //copy assignment
        Graph& operator=(const Graph& rhs);       
        //move constructor
        Graph(Graph&& rhs);          
        //move assignment
        Graph& operator=(Graph&& rhs);
        
        int get_number_of_components(string city);
        
        //added now
        int get_size();
        string get_value(int index);
        int get_index(string str);
        map<int, int> get_neighbours(int index);
               
        class iterator
        {
            private:
            Node* pt_;
            vector<Node> graph_temp_;   
            bool* visited;
            list<int> cont;
            bool last = false;
            vector<string> node_names_;
            int check;
            
    
            public:
            int counter_=0;
            iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c);
            ~iterator();
            string operator *();
            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);
            iterator& operator++(); // pre
            iterator operator++(int); // post
            
            
        };
        
        iterator begin_bfs(string str);
        iterator end_bfs(string str="$$$");
        iterator begin_dfs(string str);
        iterator end_dfs(string str="$$$");
        iterator make_itr(int c, string str);

		//void djikstra(string src_, int N);

        vector<string> topo_sort(iterator start_pt,iterator end_pt);


};
Graph::iterator myfind(Graph::iterator first, Graph::iterator last, string val);
bool comp_graphs(Graph::iterator st1,Graph::iterator en1,Graph::iterator st2,Graph::iterator en2);
