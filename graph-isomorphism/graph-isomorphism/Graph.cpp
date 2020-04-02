#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
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

