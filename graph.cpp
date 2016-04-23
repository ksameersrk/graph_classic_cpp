#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
//#include <stack>
using namespace std;

class Node
{
    private:
		static int num_of_nodes;
        int name_;
		string val_;
        map<int, int> neighbours_;
        friend class Graph;	
		friend class dfs_iterator;
 
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
        Node(string val) : val_(val) 
		{
			name_ = num_of_nodes++;
		}
		Node();
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
		bool operator==(const Node& rhs)
		{
			return name_ == rhs.name_;
		}
};
int Node::num_of_nodes = 0;
class Graph
{
    private:
        vector<Node> graph_;
        Node source_;
        Node destination_;
		int N_;
		vector<vector<int>> adj_matrix_;
        //Node* source_;
        //Node* destination_;
    public:
        /*Graph(const vector<vector<int>>& matrix,
                const Node& source=Node(), const Node& destination=Node()) 
        : source_(source), destination_(destination)
        {
            for(int i=0; i<matrix.size(); i++)
            {
                Node tmp(i, matrix[i]);
                graph_.push_back(tmp);
            }
        }*/

		Graph(const int N, const Node& source, const Node& destination)
		: N_(N), source_(source), destination_(destination)
		{
			for(int i=0; i<N_; i++)
			{
				vector<int> v{-1,-1,-1,-1}; // use iota
				adj_matrix_.push_back(v);
			}
		}
        
		void add(const Node& sc, const Node& dest, int edge_wt)
		{	
			adj_matrix_[sc.name_][dest.name_] = edge_wt;
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
		void display2()
		{
			for(int i=0; i<N_; i++)
			{
				for(int j=0; j<N_; j++)
				{
					cout << adj_matrix_[i][j] << " ";
				}
				cout << "\n";
			}
		}
		
		class dfs_iterator
		{
			private:
			Node sc;
			//stack<Node*> s;

			public:
			dfs_iterator() { } 
			dfs_iterator(const Node& p) : sc(p) { }
			
			//dereferencing			
			/*Node operator*()
			{	
				return *sc;
			}*/
			int operator*()
			{
				cout << sc.val_ << "\n";
				return sc.name_;
			}
			
			bool operator==(dfs_iterator& rhs)
			{
				return sc == rhs.sc; // this.operator==(node& rhs);
			}
			bool operator!=(dfs_iterator& rhs)
			{
				return !(sc == rhs.sc);
			}
		};	

		dfs_iterator begin()
		{
			return dfs_iterator(source_);
		}
		dfs_iterator end()
		{
			return dfs_iterator(destination_);
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

template <typename ptr_t >
void check_iterator(ptr_t first, ptr_t last)
{
	cout << "here\n";
	cout << *first << " " << *last << "\n";
	/*	
	if(first == last)
		cout << "here\n";
	else if(first != last)
		cout << "here2\n";
	*/
}
int main()
{
    int N;
    cin >> N;
    //vector<vector<int>> adjacency_matrix = input(N);
    //Graph g(adjacency_matrix);
    //g.display();

	Node sc("bnglre");
	Node dest("delhi");
	Graph g(N,sc,dest);
	
	//g.display2();
	Node a("mumbai");
	Node b("chennai");

	g.add(sc,a,1);
	g.add(a,b,2);
	g.add(b,a,3);
	g.add(dest,b,4);
	g.add(sc,dest,5);
	
	//g.display2();

	check_iterator(g.begin(),g.end());
    return 0;
}
