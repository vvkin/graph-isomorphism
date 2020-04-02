#pragma once
#include "Graph.h"
#include <sstream>

const int infinity = INT16_MAX;

// Structures for algorithms
struct bfs_result {
	int* distance;
	std::vector<int>* path;
};

enum sign {
	minus, plus
};

struct element {
	element() = default;

	element(const sign s, const int d, const int v, const int e)
		: sign(s), distance(d), vertices(v), edges(e) {}

	int number() const {
		std::stringstream in;
		in << (sign == sign::plus ? "+" : "-");
		in << distance << vertices << edges;
		return stoi(in.str());
	}

	sign sign;
	int distance;
	int vertices;
	int edges;
};


class Algorithm
{
private:
	static bfs_result bfs(Graph, int);
	template<typename T>
	static T* create_a(const T, const int);
	static element** get_sign_matrix(Graph);
public:
	template<typename T>
	static T** create_m(const T, const int);
};





