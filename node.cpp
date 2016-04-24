#include "node.h"

//default constructor
Node::Node()
:name_()
{ }

//parametrized constructor
Node::Node(int name, const vector<int>& v)
: name_(name)
{
    for(int i=0; i<v.size(); i++)
    {
        if(v[i] > 0)
        {
            neighbours_.insert(make_pair(i, v[i]));
        }
    }
}

//destructor
Node::~Node()
{ }

//copy constructor
Node::Node(const Node& rhs)
{
    name_ = rhs.name_;
    for(auto k : rhs.neighbours_)
    {
        neighbours_.insert(k);
    }
}

//copy assignment
Node& Node::operator=(const Node& rhs)
{
    if(this != &rhs)
    {
        name_ = rhs.name_;
        neighbours_.clear();
        for(auto k : rhs.neighbours_)
        {
            neighbours_.insert(k);
        }
    }
    return *this;
}

//move constructor
Node::Node(Node&& rhs)
: name_(rhs.name_), neighbours_(rhs.neighbours_)
{
    rhs.name_ = -1;
    //rhs.neighbours_ = NULL;
}

//move assignment
Node& Node::operator=(Node&& rhs)
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
