#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
//#include <stack>
//#include <cstring>
using namespace std;

class Node
{
    private:
        int name_;
        map<int, int> neighbours_;
        friend class Graph;
 
	//constructor       
    public:
        Node(int name, const vector<int>& v)
        : name_(name)
        {
            for(int i=0; i<v.size(); i++)
            {
                neighbours_.insert(make_pair(i, v[i]));
            }
        }
        
        ~Node()
        {
        }
        
        //copy constructor
        Node(const Node& rhs)
        {
            name_ = rhs.name_;
            for(auto k : rhs.neighbours_)
            {
                neighbours_.insert(k);
            }
        }
        
        //copy assignment
        Node& operator=(const Node& rhs)
        {
            if(this != &rhs)
            {
                name_ = rhs.name_;
                map<int, int> m;
                neighbours_.clear();
                for(auto k : rhs.neighbours_)
                {
                    m.insert(k);
                }
                neighbours_ = move(m);
            }
            return *this;
        }
        
        //move constructor
        Node(Node&& rhs)
        : name_(rhs.name_), neighbours_(rhs.neighbours_)
        {
            rhs.name_ = -1;
            //rhs.neighbours_ = NULL;
        }
        
        Node& operator=(Node&& rhs)
        {
            if(this != &rhs)
            {
                name_ = rhs.name_;
                neighbours_ = rhs.neighbours_;
                rhs.name_ = -1;
                //rhs.neighbours_ = NULL;
            }
            return *this;
        }
        /*
		int operator*(const Node& nd)
		{
			return nd.name_;
		}
		*/
};

class Graph
{
    private:
        vector<Node> graph_;
        Node source_;
        Node destination_;
        //Node* source_;
        //Node* destination_;
    public:
        Graph(const vector<vector<int>>& matrix,
                Node source=Node(), Node destination=Node()) 
        : source_(source), destination_(destination)
        {
            for(int i=0; i<matrix.size(); i++)
            {
                Node tmp(i, matrix[i]);
                graph_.push_back(tmp);
            }
        }
        
        void display()
        {
            for(Node n : graph_)
            {
                cout << "name : " << n.name_ << " neighbours : \n";
                for(auto k : n.neighbours_)
                {
                    cout << k.first << " " << k.second << endl;
                } 
                cout << "\n";
            }
        }
		/*
		dfs_iterator begin()
		{
			return dfs_iterator(source);
		}
		dfs_iterator end()
		{
			return dfs_iterator(destination);
		}
		*/
		class dfs_iterator
		{
			private:
			Node* sc;
			//stack<Node*> s;

			public:
			dfs_iterator() { } 
			dfs_iterator(Node* p) : sc(p) { }
			
			//dereferencing			
			/*Node operator*()
			{	
				return *sc;
			}*/
			int operator*()
			{
				return sc->name_;
			}
			bool operator==(dfs_iterator& rhs)
			{
				return sc == rhs.sc;
			}
			bool operator!=(dfs_iterator& rhs)
			{
				return !(sc == rhs.sc);
			}
		};	

};

vector<vector<int>> input(int N)
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

int main()
{
    int N;
    cin >> N;
    //vector<vector<int>> adjacency_matrix = input(N);
    //Graph g(adjacency_matrix);
    //g.display();

	Graph g();
	g.add(Node(),Node(),3);
    return 0;
}
