#include "Graph.h"
#include <iostream>

using std::cout;
using std::vector;

Graph::Graph(int vertices_num, int edges_num, Edge* edges_list){
	this->vertices_num = vertices_num;
	this->edges_num = edges_num;
	this->edges_list = new Edge[this->vertices_num];
	for (int i = 0; i < vertices_num; ++i)
		this->edges_list[i] = edges_list[i];
}

Graph::Graph(const Graph& graph)
{
	this->vertices_num = graph.vertices_num;
	this->edges_num = graph.edges_num;
	this->edges_list = new Edge[this->edges_num];
	for (int i = 0; i < this->edges_num; ++i)
		this->edges_list[i] = graph.edges_list[i];
}

Graph::Graph() {};

Graph::~Graph(){
	delete[] this->edges_list;
}

Graph Graph::delete_edge(int begin, int end){
	Edge* new_edges_list = new Edge[this->edges_num];
	int iterator = 0;

	for (int i = 0; i < this->edges_num; ++i) {
		if (this->edges_list[i].in != begin && this->edges_list[i].out != end) {
			new_edges_list[iterator++] = this->edges_list[i];
		}
	}
	return Graph(this->vertices_num, this->edges_num-(this->edges_num-iterator), new_edges_list);
}

void Graph::get_info(){
	cout << "information about current graph\n";
	cout << "Vertices : " << this->vertices_num << '\n';
	cout << "Edges number : " << this->edges_num << '\n';
	cout << "Edges : \n";
	for (int i = 0; i < this->edges_num; ++i) {
		cout << this->edges_list[i].in << " " << this->edges_list[i].out << '\n';
	}
}

vector<vector<int> > Graph::create_adjacency_list(){
	vector<vector<int>> adj_list(this->vertices_num);
	for (int i = 0; i < this->vertices_num; ++i) {
		adj_list[this->edges_list[i].in].push_back(this->edges_list[i].out);
		adj_list[this->edges_list[i].out].push_back(this->edges_list[i].in);
	}
	return adj_list;
}

int** Graph::get_adjacency_matrix() {
	int** adj_m = Algorithm::create_m(0, this->vertices_num);
	for (auto i = 0; i < this->edges_num; ++i) {
		if (this->edges_list[i].out == this->edges_list[i].in) continue;
		adj_m[this->edges_list[i].out][this->edges_list[i].in] = 1;
		adj_m[this->edges_list[i].in][this->edges_list[i].out] = 1;
	}
	return adj_m;
}

