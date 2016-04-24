class Graph
{
	private:
    vector<Node> graph_;
    vector<string> node_names_;
    map<string, int> name_index_;
	public:
	Graph();
	Graph(const vector<vector<int>>& matrix,
                vector<string> node_names);
	~Graph();
	Graph(const Graph& rhs);
	Graph& operator=(const Graph& rhs);
	Graph(Graph&& rhs);
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
        iterator& operator++() // pre
	};
};
