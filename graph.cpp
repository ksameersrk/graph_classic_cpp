#include "graph.h"

//default ctor
Graph::Graph()
{}

//constructor
Graph::Graph(const vector<vector<int>>& matrix,
        vector<string> node_names) 
{
    for(int i=0; i<matrix.size(); i++)
    {
        Node tmp(i, matrix[i]);
        graph_.push_back(tmp);
    }
    for(int i=0; i<node_names.size(); i++)
    {
        node_names_.push_back(node_names[i]);
        name_index_[node_names[i]] = i;
    }
}

//destructor
Graph::~Graph()
{ }

//copy constructor
Graph::Graph(const Graph& rhs)
{
    for(auto k : rhs.graph_)
    {
        graph_.push_back(k);
    }
    for(auto k : rhs.node_names_)
    {
        node_names_.push_back(k);
    }
}

//copy assignment
Graph& Graph::operator=(const Graph& rhs)
{
    if(this != &rhs)
    {
        graph_.clear();
        node_names_.clear();
        for(auto k : rhs.graph_)
        {
            graph_.push_back(k);
        }
        for(auto k : rhs.node_names_)
        {
            node_names_.push_back(k);
        }
    }
    return *this;
}

//move constructor
Graph::Graph(Graph&& rhs)
{
    graph_ = move(rhs.graph_);
    node_names_ = move(rhs.node_names_);
}

//move assignment
Graph& Graph::operator=(Graph&& rhs)
{
    if(this != &rhs)
    {
        graph_ = move(rhs.graph_);
        node_names_ = move(rhs.node_names_);
    }
    return *this;
}


Graph::iterator::iterator(Node* sc, vector<Node> graph_temp, vector<string> node_names,int c)
:visited(new bool[graph_temp.size()]), pt_(sc), graph_temp_(graph_temp),check(c)
{
    for(int i=0; i<graph_temp.size(); i++)
    {
        visited[i] = false;
    }
        
    for(int i=0; i<node_names.size(); i++)
    {
        node_names_.push_back(node_names[i]);
    }
}
string Graph::iterator::operator *()
{
    return node_names_[pt_->name_];
}
bool Graph::iterator::operator==(const iterator& rhs)
{
    return pt_->name_ == rhs.pt_->name_;
}
bool Graph::iterator::operator!=(const iterator& rhs)
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

Graph::iterator& Graph::iterator::operator++() // pre
{
    if(! visited[pt_->name_])
    {
        visited[pt_->name_] = true;
    }

    vector<int> temp;
    for(auto k : pt_->neighbours_)
    {
            temp.push_back(k.first);
    }

    for(int i : temp) 
    {
        if(! visited[i])
            cont.push_back(i);
    }
    if(! cont.empty())
    {
        if(check == 1)
        {
            pt_ = &graph_temp_[cont.back()];
            cont.pop_back();
        }

        else
        {
            pt_ = &graph_temp_[cont.front()];
            cont.pop_front();
        }
    }
    return *this;
}   

Graph::iterator Graph::iterator::operator++(int) // post
{                
    iterator temp (*this);
    ++*this;
    return temp;
}
    
Graph::iterator Graph::begin_bfs(string str)
{
    return begin(BFS, str);
}
Graph::iterator Graph::end_bfs(string str)
{
    return end(BFS, str);
}
Graph::iterator Graph::begin_dfs(string str)
{
    return begin(DFS, str);
}
Graph::iterator Graph::end_dfs(string str)
{
    return end(DFS, str);
}
Graph::iterator Graph::begin(int c, string str)
{
    return iterator(&graph_[name_index_[str]], graph_, node_names_, c);
}
Graph::iterator Graph::end(int c, string str)
{
    return iterator(&graph_[name_index_[str]], graph_, node_names_, c);
}
