#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
//#include <cstring>
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
    	Node()
    	:name_()
    	{}

    	//parametrized constructor
        Node(int name, const vector<int>& v)
        : name_(name)
        {
            for(int i=0; i<v.size(); i++)
            {
                neighbours_.insert(make_pair(i, v[i]));
            }
        }
        
        //destructor
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
        
        //move assignment
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
        
};

class Graph
{
    private:
        int source_;
        int destination_;
        vector<Node> graph_;

    public:
        Graph(const vector<vector<int>>& matrix,
                int src = 0,int dest = 0) 
        : source_(src), destination_(dest)
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

        //bfs iterator
        class bfs_iterator
        {
        	private:
        	Node *pt_;
        	list<int> queue;
        	vector<int> visited;
        	vector<Node> temp_;

        	public:
        	//default ctor
        	bfs_iterator()
        	//: to do
        	{}
        	
        	//constructor
        	bfs_iterator(Node *rhs,vector<Node> g)
        	:pt_(rhs),temp_(g){queue.clear();visited.clear();}


        	//destructor
        	~bfs_iterator()
        	{}
    
        	//dereferencing
        	int operator *()
        	{
        		return pt_->name_;
        	}

        	bool operator ==(bfs_iterator rhs)
        	{
        		return pt_->name_ == rhs.pt_->name_;
        	}

        	bool operator !=(bfs_iterator rhs)
        	{
        		return !(pt_ == rhs.pt_);
        	}

        	bfs_iterator& operator ++()
        	{
        		cout << "Visited size : " << visited.size() << endl;
        		if(find(begin(visited),end(visited),pt_->name_) == visited.end())
        		{
        			visited.push_back(pt_->name_);
        			cout<<"NAME = "<<pt_->name_<<"\n";
        		}

        		for(auto k : pt_->neighbours_)
        		{	
        			if(find(begin(visited),end(visited),k.first) == visited.end() && k.second > 0)
    				{
    					queue.push_back(k.first);
    				}
    			}

        		pt_ = &temp_[queue.front()];
        		queue.pop_front();

        		cout<<"Queue:\t";
        		for(int l : queue)
        			cout<<l<<"\t";
        		cout << endl;

        		return *this;

        	}

        };

        bfs_iterator begin_g()
        {
        	return bfs_iterator(&graph_[source_],graph_);
        }

        bfs_iterator end_g()
        {
        	return bfs_iterator(&graph_[destination_],graph_);
        }

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
    //names mapping
    vector<vector<int>> adjacency_matrix = input(N);
    Graph g(adjacency_matrix,0,1);
    //g.display();

    auto it = g.begin_g();
    auto end = g.end_g();
    while(it != end)
    {
    	cout << *it << endl;
    	++it;
    }

    return 0;
}
