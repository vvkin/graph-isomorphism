#include "Graph.h"

Graph::Graph(int vertices_num, int edges_num, std::vector<Edge> edges_list)
{
	this->vertices_num = vertices_num;
	this->edges_num = edges_num;
	std::copy(this->edges_list.begin(), this->edges_list.end(), back_inserter(edges_list));
}

