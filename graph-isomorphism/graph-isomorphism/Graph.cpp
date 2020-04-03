#include "Graph.h"
#include <iostream>

using std::cout;
using std::vector;

Graph::Graph(const int vertices_num, const int edges_num, Edge* edges_list){
	this->vertices_num = vertices_num;
	this->edges_num = edges_num;
	this->edges_list = new Edge[this->edges_num];
	for (auto i = 0; i < edges_num; ++i)
		this->edges_list[i] = edges_list[i];
}

Graph::Graph(const Graph& graph)
{
	this->vertices_num = graph.vertices_num;
	this->edges_num = graph.edges_num;
	this->edges_list = new Edge[this->edges_num];
	for (auto i = 0; i < this->edges_num; ++i)
		this->edges_list[i] = graph.edges_list[i];
}

Graph::Graph() {};

Graph::~Graph(){
	delete[] this->edges_list;
}

Graph Graph::delete_edge(const int begin, const int end){
	auto* new_edges_list = new Edge[this->edges_num];
	auto iterator = 0;

	for (auto i = 0; i < this->edges_num; ++i) {
		if (this->edges_list[i].out == begin && this->edges_list[i].in == end) continue;
		new_edges_list[iterator] = this->edges_list[i]; ++iterator;
	}

	return Graph(this->vertices_num, iterator, new_edges_list);
}

void Graph::get_info(){
	cout << "information about current graph\n";
	cout << "Vertices : " << this->vertices_num << '\n';
	cout << "Edges number : " << this->edges_num << '\n';
	cout << "Edges : \n";
	for (auto i = 0; i < this->edges_num; ++i) {
		cout << this->edges_list[i].out + 1 << " " << this->edges_list[i].in + 1 << '\n';
	}
}

vector<vector<int> > Graph::create_adjacency_list(){
	vector<vector<int>> adj_list(this->vertices_num);
	for (auto i = 0; i < this->edges_num; ++i) {
		adj_list[this->edges_list[i].in].push_back(this->edges_list[i].out);
		adj_list[this->edges_list[i].out].push_back(this->edges_list[i].in);
	}
	return adj_list;
}


int** Graph::create_adjacency_matrix() {
	auto** adj_m = this->create_m(0);
	for (auto i = 0; i < this->edges_num; ++i) {
		if (this->edges_list[i].in == this->edges_list[i].out) continue;
		adj_m[this->edges_list[i].in][this->edges_list[i].out] = 1;
		adj_m[this->edges_list[i].out][this->edges_list[i].in] = 1;
	}
	return adj_m;
}

