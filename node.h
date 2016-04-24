#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#define BFS 0
#define DFS 1

using namespace std;

class Node
{
    private:
        int name_;
        map<int, int> neighbours_;
        friend class Graph;
        friend class bfs_iterator;
        
    public:
        //default constructor
        Node();
        //parametrized constructor
        Node(int name, const vector<int>& v);       
        //destructor
        ~Node();       
        //copy constructor
        Node(const Node& rhs);        
        //copy assignment
        Node& operator=(const Node& rhs);            
        //move constructor
        Node(Node&& rhs);        
        //move assignment
        Node& operator=(Node&& rhs);              
};