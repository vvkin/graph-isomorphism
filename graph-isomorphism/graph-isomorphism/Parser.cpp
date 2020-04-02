#include "Parser.h"
#include <fstream>

Graph Parser::parse(const char* file_name) {

	Edge* edges_list;
	int vertices_num;
	int edges_num;
	std::ifstream file_handler(file_name);

	file_handler >> vertices_num >> edges_num;
	edges_list = new Edge[vertices_num];

	for (int i = 0; i < edges_num; ++i) {
		Edge edge{};
		file_handler >> --edge.in >> --edge.out;
		edges_list[i] = edge;
	}
	return Graph(vertices_num, edges_num, edges_list);
}
