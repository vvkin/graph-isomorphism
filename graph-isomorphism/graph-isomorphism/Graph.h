#pragma once
#include "Structures.h"

class Graph {
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
	int** create_adjacency_matrix();
	template<typename T>
	T** create_m(T);

	friend class Algorithm;
};


template<typename T>
T** Graph::create_m(const T filler)
{
	auto** matrix = new T * [this->vertices_num];
	for (auto i = 0; i < this->vertices_num; ++i) {
		matrix[i] = new T[this->vertices_num];
	}
	for (auto i = 0; i < this->vertices_num; ++i) {
		for (auto j = 0; j < this->vertices_num; ++j) {
			matrix[i][j] = filler;
		}
	}
	return matrix;
}
