#pragma once
#include <vector>

struct Edge {
	int in;
	int out;
};

class Graph{
private:
	std::vector<Edge> edges_list{};
	int vertices_num;
	int edges_num;

public:
	Graph(int, int, std::vector<Edge>);


};

