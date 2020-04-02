#include "Graph.h"
#include <iostream>
using std::cout;

Graph::Graph(int vertices_num, int edges_num, Edge* edges_list){
	this->vertices_num = vertices_num;
	this->edges_num = edges_num;
	this->edges_list = new Edge[this->vertices_num];
	for (int i = 0; i < vertices_num; ++i)
		this->edges_list[i] = edges_list[i];
}

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

void Graph::get_info()
{
	cout << "information about current graph\n";
	cout << "Vertices : " << this->vertices_num << '\n';
	cout << "Edges number : " << this->edges_num << '\n';
	cout << "Edges : \n";
	for (int i = 0; i < this->edges_num; ++i) {
		cout << this->edges_list[i].in << " " << this->edges_list[i].out << '\n';
	}

}

