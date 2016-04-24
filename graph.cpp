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
        
    public:
    	//default constructor
    	Node()
    	:name_(-1)
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
        vector<Node> graph_;
        int source_;
        int destination_;
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
        /*
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
		*/
/*
        //bfs iterator
        class bfs_iterator
        {
        	private:
        	Node *pt_;

        	//constructor
        	bfs_iterator(Node *rhs)
        	:pt_(rhs){}

        	//dereferencing
        	int operator *()
        	{
        		return pt_->name_;
        	}

        	bool operator ==(bfs_iterator rhs)
        	{
        		return pt_ == rhs.pt_;
        	}

        	bool operator !=(bfs_iterator rhs)
        	{
        		return !(pt_ == rhs.pt_);
        	}

        	Node operator ++()
        	{
        		//to be done
        	}

        };
*/
		class dfs_iterator
		{
			private:
			Node* pt_;
			vector<Node> graph_temp_;
			//int src;	
			int n = 4;
			//vector<int> visited;
			int* visited;
			list<int> stack; 
			public:
			dfs_iterator(Node* sc, vector<Node> graph_temp)
			:visited(new int[graph_temp.size()]), pt_(sc), graph_temp_(graph_temp)
			{
				//cout << pt_->name_ << "\n";
				//pt_ = SC;		
				//fill(visited.begin(),visited.end(),-1);
				for(int i=0; i<graph_temp.size(); i++)
					visited[i] = -1;
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
				//return !(pt_->name_ == rhs.pt_->name_);
				return !(*this == rhs);
			}

			#if 1
			dfs_iterator& operator++() // pre
			{
				if(visited[pt_->name_] == -1)
					visited[pt_->name_] = 1;
				vector<int> temp;
				for(auto k : pt_->neighbours_)
				{
					if(k.second > 0)
						temp.push_back(k.first);
				}
		
				for(int i : temp) 
				{
					if(visited[i] == -1)
						stack.push_back(i);
				}
				pt_ = &graph_temp_[stack.back()];
				cout << "pt_.name_ = " << pt_->name_ << "\n";
				stack.pop_back();
				return *this;
			}
			#endif		
			
			
		};

		dfs_iterator begin()
		{
			return dfs_iterator(&graph_[source_],graph_);
		}
		dfs_iterator end()
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

int main()
{
    int N;
    cin >> N;
    //names mapping
    vector<vector<int>> adjacency_matrix = input(N);
    Graph g(adjacency_matrix,0,2);
    //g.display();
	auto first = g.begin();
	auto last = g.end();
	cout << *first << "\n";
	cout << *last << "\n";
/*
	++first;
	cout << *first << "\n";   
	++first;
	cout << *first << "\n";   
	++first;
	cout << *first << "\n";   
*/
	do//while(first != last)
	{
		cout << "first = " <<  *first << "\n";
		++first;
	}while(first != last)
	//cout << "first = " << *first << "\n";
	return 0;
}
