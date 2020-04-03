#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;
using std::vector;

const int infinity = INT16_MAX;

struct bfs_result {
	int* distance;
	std::vector<int>* path;
};

enum sign {
	minus, plus
};

struct Edge {
	int in;
	int out;
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

	bool operator!=(const element& other) const {
		return this->number() != other.number();
	}
	
	sign sign;
	int distance;
	int vertices;
	int edges;
};
