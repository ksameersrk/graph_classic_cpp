#include "node.h"

class Graph
{
    private:
        vector<Node> graph_;
        vector<string> node_names_;
        map<string, int> name_index_;
        
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
            iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c);
            string operator *();
            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);
            iterator& operator++(); // pre
            iterator operator++(int); // post
            
        };
        
        iterator begin_bfs(string str);
        iterator end_bfs(string str);
        iterator begin_dfs(string str);
        iterator end_dfs(string str);
        iterator begin(int c, string str);
        iterator end(int c, string str);

};

