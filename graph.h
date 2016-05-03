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
               
        class my_iterator : public iterator<forward_iterator_tag, Node*>
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
            my_iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c);
            ~my_iterator();
            string operator *();
            bool operator==(const my_iterator& rhs);
            bool operator!=(const my_iterator& rhs);
            my_iterator& operator++(); // pre
            my_iterator operator++(int); // post
            
            string operator->();
            
            
        };
        
        my_iterator begin_bfs(string str);
        my_iterator end_bfs(string str="$$$");
        my_iterator begin_dfs(string str);
        my_iterator end_dfs(string str="$$$");
        my_iterator make_itr(int c, string str);

		//void djikstra(string src_, int N);

        vector<string> topo_sort(my_iterator start_pt,my_iterator end_pt);


};
Graph::my_iterator myfind(Graph::my_iterator first, Graph::my_iterator last, string val);
bool comp_graphs(Graph::my_iterator st1,Graph::my_iterator en1,Graph::my_iterator st2,Graph::my_iterator en2);
