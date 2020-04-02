#include "Parser.h"
#include <fstream>

Graph Parser::parse(const char* file_name) {

	int vertices_num, edges_num;
	std::ifstream file_handler(file_name);

	file_handler >> vertices_num >> edges_num;
	auto* edges_list = new Edge[edges_num];

	for (auto i = 0; i < edges_num; ++i) {
		Edge edge = {};
		file_handler >> edge.out >> edge.in;
		--edge.in; --edge.out;
		edges_list[i] = edge;
	}

	file_handler.close();
	return Graph(vertices_num, edges_num, edges_list);
}
