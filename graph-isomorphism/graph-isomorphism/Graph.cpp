#include "Graph.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int infinity = INT16_MAX;

struct edge {
	int out;
	int in;
};

struct bfs_result {
	int* distance;
	vector<int>* path;
};

template<typename T>
T* create_a(const T filler, const int size) {
	auto* array_ = new T[size];
	for (auto i = 0; i < size; ++i) {
		array_[i] = filler;
	}
	return array_;
}

template<typename T>
T** create_m(const T filler, const int size) {
	auto** matrix = new T * [size];
	for (auto i = 0; i < size; ++i) {
		matrix[i] = new T[size];
	}
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			matrix[i][j] = filler;
		}
	}
	return matrix;
}

vector<vector<int>> create_adjacency_list(edge* edges, const int vertex, const int edge_amount) {
	vector<vector<int>> adj_l(vertex);
	for (auto i = 0; i < edge_amount; ++i) {
		adj_l[edges[i].out].push_back(edges[i].in);
		adj_l[edges[i].in].push_back(edges[i].out);
	}
	return adj_l;
}

bfs_result bfs(vector<vector<int>>& adj_l, const int size, const int start) {

	auto* visit = create_a(false, size);
	auto* dist = create_a(infinity, size);
	auto* prev = create_a(-infinity, size);

	queue<int> q;
	q.push(start);
	dist[start] = 0;
	visit[start] = true;

	while (!q.empty()) {
		const auto parent = q.front();
		for (auto& child : adj_l[parent]) {
			const auto new_dist = dist[parent] + 1;
			if (!visit[child]) {
				visit[child] = true;
				dist[child] = new_dist;
				prev[child] = parent;
				q.push(child);
			}
		}
		q.pop();
	}

	auto* path = create_a(vector<int>(), size);
	for (auto i = 0; i < size; ++i) {
		if (i == start) {
			path[i].push_back(start);
		}
		else if (prev[i] == -infinity) {
			path[i] = {};
		}
		else {
			for (auto at = prev[i]; at != start;) {
				path[i].push_back(at);
				at = prev[at];
			}
			path[i].push_back(start);
			reverse(begin(path[i]), end(path[i]));
		}
	}

	delete[] visit;
	delete[] prev;

	return { dist, path };
}

int** create_adjacency_matrix(edge* edges, const int vertex, const int edge_amount) {
	auto** adj_m = create_m(0, vertex);
	for (auto i = 0; i < edge_amount; ++i) {
		if (edges[i].out == edges[i].in) continue;
		adj_m[edges[i].out][edges[i].in] = 1;
		adj_m[edges[i].in][edges[i].out] = 1;
	}
	return adj_m;
}

enum sign {
	minus, plus
};

struct element {
	element() = default;

	element(const sign s, const int d, const int v, const int e)
		: sign(s), distance(d), vertices(v), edges(e) {}

	int number() const {
		stringstream in;
		in << (sign == sign::plus ? "+" : "-");
		in << distance << vertices << edges;
		return stoi(in.str());
	}

	sign sign;
	int distance;
	int vertices;
	int edges;
};

element** get_sign_matrix(int** adg_m, vector<vector<int>>& adj_l, edge* edges, const int vertex) {
	auto** sign_m = create_m(element(), vertex);

	for (auto i = 0; i < vertex; ++i) {
		for (auto j = 0; j < vertex; ++j) {
			element object = {};

			object.sign = adg_m[i][j] ? sign::plus : sign::minus;

			const auto start = bfs(adj_l, vertex, i);
			const auto end = bfs(adj_l, vertex, j);

			object.distance = start.distance[j];

			set<int> pair_graph;
			for (auto k = 0; k < vertex; ++k) {
				if (start.path[k].back() != end.path[k].back() || int(start.path[k].size()
					+ end.path[k].size()) != object.distance) continue;

				for (auto& item : start.path[k]) {
					if (pair_graph.find(item) == pair_graph.end()) {
						pair_graph.insert(item);
					}
				}

				for (auto& item : end.path[k]) {
					if (pair_graph.find(item) == pair_graph.end()) {
						pair_graph.insert(item);
					}
				}
			}

			object.vertices = pair_graph.size();

			for (auto& node : pair_graph) {
				for (auto& neighbor : adj_l[node]) {
					if (pair_graph.find(neighbor) != pair_graph.end()) {
						++object.edges;
					}
				}
			}

			delete[] start.path; delete start.distance;
			delete[] end.path; delete[] end.distance;

			sign_m[i][j] = object;
		}
	}

	return sign_m;
}

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

