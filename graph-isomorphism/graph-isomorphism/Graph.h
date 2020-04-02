#pragma once
#include <vector>
#include "Algorithm.h";

struct Edge {
	int in;
	int out;
};

class Graph {
private:
	Edge* edges_list;
	int vertices_num;
	int edges_num;

public:
	Graph(int, int, Edge*);
	Graph(const Graph&);
	Graph();
	~Graph();

	Graph delete_edge(int, int);
	void get_info();
	std::vector<std::vector<int>> create_adjacency_list();
	int** get_adjacency_matrix();

	friend class Algorithm;
};

