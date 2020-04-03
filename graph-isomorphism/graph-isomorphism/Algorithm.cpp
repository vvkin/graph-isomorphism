#include "Algorithm.h"
#include <queue>
#include <set>
#include "Printer.h"

using std::queue;
using std::set;
using std::vector;


template<typename T>
T* Algorithm::create_a(const T filler, const int size) {
	auto* array = new T[size];
	for (auto i = 0; i < size; ++i) {
		array[i] = filler;
	}
	return array;
}

bfs_result Algorithm::bfs(Graph& graph, const int start) {

	auto* visit = create_a(false, graph.vertices_num);
	auto adj_list = graph.create_adjacency_list();
	auto* dist = create_a(infinity, graph.vertices_num);
	auto* prev = create_a(-infinity, graph.vertices_num);

	queue<int> q;
	q.push(start);
	dist[start] = 0;
	visit[start] = true;

	while (!q.empty()) {
		const auto parent = q.front();
		for (auto& child : adj_list[parent]) {
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

	auto* path = create_a(vector<int>(), graph.vertices_num);
	for (auto i = 0; i < graph.vertices_num; ++i) {
		if (i == start) {
			path[i].push_back(start);
		}
		else if (prev[i] == -infinity) {
			path[i] = {};
		}
		else {
			for (auto at = i; at != start;) {
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


element** Algorithm::get_sign_matrix(Graph& graph) {
	auto** sign_m = graph.create_m(element());
	auto** adj_m = graph.create_adjacency_matrix();
	auto adj_l = graph.create_adjacency_list();

	for (auto i = 0; i < graph.vertices_num; ++i){
		for (auto j = 0; j < graph.vertices_num; ++j) {
			element object = {};

			object.sign = adj_m[i][j] ? plus : minus;

			auto new_graph = graph.delete_edge(i, j);
			const auto start = bfs(new_graph, i);
			const auto end = bfs(new_graph, j);
			
			object.distance = start.distance[j];

			set<int> pair_graph;
			for (auto k = 0; k < new_graph.vertices_num; ++k) {
				if (start.path[k].back() != end.path[k].back() || int(start.path[k].size()
					+ end.path[k].size() - 2) != object.distance) continue;
				
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

			object.edges /= 2;
			
			delete[] start.path; delete start.distance;
			delete[] end.path; delete[] end.distance;

			sign_m[i][j] = object;
		}
	}
	return sign_m;
}

bool Algorithm::is_isomorphic(Graph& A, Graph& B) {
	//Call all function to check are graphs isomorphic
	return true;
}


std::vector<element> Algorithm::get_lexicographical_order(Graph& graph)
{
	auto compare = [](const element& lhs, const element& rhs) {
		return lhs.sign == rhs.sign ? abs(lhs.number()) < 
			abs(rhs.number()) : lhs.number() < rhs.number();
	};
	
	set<element, decltype(compare)> unique_elements(compare);

	auto** sign_m = Algorithm::get_sign_matrix(graph);
	const auto size = graph.vertices_num;

	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			unique_elements.insert(sign_m[i][j]);
		}
	}

	return (vector<element>(unique_elements.begin(), unique_elements.end()));
}







