#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>

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
        
		class dfs_iterator
		{
			private:
			Node* pt_;
			vector<Node> graph_temp_;	
			bool* visited;
			list<int> stack;
			bool last = false; 
			
			public:
			dfs_iterator(Node* sc, vector<Node> graph_temp)
			:visited(new bool[graph_temp.size()]), pt_(sc), graph_temp_(graph_temp)
			{
				for(int i=0; i<graph_temp.size(); i++)
					visited[i] = false;
			}
			int operator*()
			{
				return pt_->name_;
			}
			bool operator==(const dfs_iterator& rhs)
			{
				return pt_->name_ == rhs.pt_->name_;
			}
			bool operator!=(const dfs_iterator& rhs)
			{
				if(last)
        		{
        		    return false;
        		}
        		else
        		{
        		    if(*this == rhs)
        		    {
        		        last = true;
        		    }
        		    return true;
        		}
			}

			dfs_iterator& operator++() // pre
			{
				if(! visited[pt_->name_])
			    {
			        visited[pt_->name_] = true;
			    }
				vector<int> temp;
				for(auto k : pt_->neighbours_)
				{
					if(k.second > 0)
						temp.push_back(k.first);
				}
		
				for(int i : temp) 
				{
					if(! visited[i])
						stack.push_back(i);
				}
				if(! stack.empty())
				{
				    pt_ = &graph_temp_[stack.back()];
				    stack.pop_back();
				}
				return *this;
			}	
			
		};

        //bfs iterator
        class bfs_iterator
        {
        	private:
        	Node *pt_;
        	list<int> queue;
        	bool *visited;
        	vector<Node> graph_temp_;
        	bool last = false;

        	public:
        	//default ctor
        	bfs_iterator()
        	//: to do
        	{}
        	
        	//constructor
        	bfs_iterator(Node *rhs,vector<Node> g)
        	:pt_(rhs), graph_temp_(g), visited(new bool[g.size()])
        	{
        	    for(int i=0; i<g.size(); i++)
        	    {
        	        visited[i] = false;
        	    }
        	}


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
        		if(last)
        		{
        		    return false;
        		}
        		else
        		{
        		    if(*this == rhs)
        		    {
        		        last = true;
        		    }
        		    return true;
        		}
        	}

        	bfs_iterator& operator ++()
        	{
        	    
        		if(! visited[pt_->name_])
        		{
        			visited[pt_->name_] = true;
        		}
        		for(auto k : pt_->neighbours_)
        		{	
        			if(! visited[k.first] &&
        			    find(begin(queue), end(queue), k.first) == queue.end() &&
        			    k.second > 0)
    				{
    					queue.push_back(k.first);
    				}
    			}
    			if(!queue.empty())
    			{
            		pt_ = &graph_temp_[queue.front()];
            		queue.pop_front();
                }
        		return *this;

        	}

        };

        bfs_iterator begin_bfs()
        {
        	return bfs_iterator(&graph_[source_],graph_);
        }

        bfs_iterator end_bfs()
        {
        	return bfs_iterator(&graph_[destination_],graph_);
        }

		dfs_iterator begin_dfs()
		{
			return dfs_iterator(&graph_[source_],graph_);
		}
		dfs_iterator end_dfs()
		{
			return dfs_iterator(&graph_[destination_],graph_);
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

template<typename ptr>
void disp(ptr first, ptr last)
{
    while(first != last)
    {
        cout << *first << "   ";
        ++first;
    }
    cout << endl;
}

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> adjacency_matrix = input(N);
    Graph g(adjacency_matrix, 0, 1);
    cout << "BFS : ";
    disp(g.begin_bfs(), g.end_bfs());
    cout << "DFS : ";
    disp(g.begin_dfs(), g.end_dfs());
    return 0;
}
