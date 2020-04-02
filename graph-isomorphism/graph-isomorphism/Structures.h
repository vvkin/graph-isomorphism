#pragma once
#include <vector>
#include <sstream>
#include <iostream>

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
		in << (sign == plus ? "+" : "-");
		in << distance << vertices << edges;
		return stoi(in.str());
	}

	bool operator!=(const element& other) const {
		return this->number() != other.number();
	}

	std::ostream& operator<<(std::ostream& out) const {
		out << (this->sign == plus ? "+" : "-") << this->distance
			<< "." << this->vertices << "." << this->edges;
		return out;
	}
	
	sign sign;
	int distance;
	int vertices;
	int edges;
};
