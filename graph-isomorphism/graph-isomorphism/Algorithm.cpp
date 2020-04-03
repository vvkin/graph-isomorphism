#include "Algorithm.h"
#include "Printer.h"
#include <queue>
#include <set>
#include <iostream>
#include <string>

using std::queue;
using std::set;
using std::vector;
using std::swap;


template<typename T>
T* Algorithm::create_a(const T filler, const int size) {
	auto* array = new T[size];
	for (auto i = 0; i < size; ++i) {
		array[i] = filler;
	}
	return array;
}

Algorithm::Algorithm(Graph& a, Graph& b){
	this->a = Graph(a);
	this->b = Graph(b);
	this->size = a.vertices_num;

	this->sign_m_a = Algorithm::get_sign_matrix(a);
	this->sign_m_b = Algorithm::get_sign_matrix(b);

	this->frequency_vector_a = get_frequency_vector(get_lexicographical_order(sign_m_a), sign_m_a);
	this->frequency_vector_b = get_frequency_vector(get_lexicographical_order(sign_m_b), sign_m_b);

	this->sort_order_a = get_sort_order(frequency_vector_a);
	this->sort_order_b = get_sort_order(frequency_vector_b);

	this->sorted_frequency_a = get_sorted_frequency_vector(frequency_vector_a, sort_order_a);
	this->sorted_frequency_b = get_sorted_frequency_vector(frequency_vector_b, sort_order_b);

	this->canon_m_a = get_canonical_form(sort_order_a, sign_m_a);
	this->canon_m_b = get_canonical_form(sort_order_b, sign_m_b);
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

bool Algorithm::is_isomorphic() {
	return main_procedure();
}


std::vector<element> Algorithm::get_lexicographical_order(element** sign_m) {
	
	auto compare = [](const element& lhs, const element& rhs) {
		if (rhs.number() < 0 && lhs.number() < 0) {
			if (lhs.distance == rhs.distance) return (abs(lhs.number()) < abs(rhs.number()));
			else return (lhs.distance > rhs.distance);
		}
		else return (lhs.number() < rhs.number());
	};
	
	set<element, decltype(compare)> unique_elements(compare);

	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			unique_elements.insert(sign_m[i][j]);
		}
	}

	return (vector<element>(unique_elements.begin(), unique_elements.end()));
}


int* Algorithm::get_sort_order(int** frequency_vector) {
	int* sort_order = new int[size];
	const auto row_size = sizeof(*frequency_vector) / sizeof(int*);

	for (auto i = 0; i < size; ++i) {
		sort_order[i] = i;
	}
	
	std::string* col_num = new std::string[size];
	for (auto i = 0; i < size; ++i) col_num[i] = "";

	for (auto j = 0; j < size; ++j) {
		for (auto i = 0; i < row_size; ++i) {
			col_num[j] += std::to_string(frequency_vector[i][j]);
		}
	}

	for (auto i = 0; i < size - 1; ++i) {
		for (auto j = 0; j < size - i - 1; ++j) {
			if (col_num[j] > col_num[j + 1]) {
				swap(col_num[j], col_num[j + 1]);
				swap(sort_order[j], sort_order[j + 1]);
			}
		}
	}

	delete[] col_num;

	return sort_order;

	delete[] sort_order;
}

element** Algorithm::get_canonical_form(int* sort_order, element** sign_m)
{
	element** sorted_sign_m = new element * [size];

	for (auto i = 0; i < size; ++i)
		sorted_sign_m[i] = new element[size];
	
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			sorted_sign_m[i][j] = sign_m[sort_order[i]][sort_order[j]];
		}
	}
	
	return sorted_sign_m;
}


template<typename T>
bool equals(T** lhs, T** rhs, const int row_size, const int col_size) {
	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			if (lhs[i][j] != rhs[i][j])
				return false;
		}
	}
	return true;
}

 bool Algorithm::swap_procedure() {
	auto const size = a.vertices_num;
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			if (canon_m_a[i][j] != canon_m_b[i][j]) {
				for (auto k = j + 1; k < size; ++k) {
					auto suitable = true;
					for (auto h = 0; h <= i; ++h) {
						if (canon_m_a[h][j] != canon_m_b[h][k]) {
							suitable = false; break;
						}
					}
					if (suitable) {
						for (auto h = 0; h < size; ++h) {
							swap(canon_m_b[h][j], canon_m_b[h][k]);
						}
						swap(canon_m_b[j], canon_m_b[k]);
						swap(sort_order_b[j], sort_order_b[k]);
					}
				}
			}
		}
	}
	return equals(canon_m_a, canon_m_b, size, size);
}

int** Algorithm::get_frequency_vector(std::vector<element> lexic_order, element** sign_m)
{
	int** frequency_vector = new int* [lexic_order.size()];

	for(auto i = 0; i < size; ++i) frequency_vector[i] = new int[size];

	for (auto i = 0; i < lexic_order.size(); ++i)
		for (auto j = 0; j < size; ++j)
			frequency_vector[i][j] = 0;

	for (auto k = 0; k < lexic_order.size(); ++k) {
		for (auto i = 0; i < size; ++i) {
			for (auto j = 0; j < size; ++j) {
				if (sign_m[i][j].number() == lexic_order[k].number())
					++frequency_vector[k][i];
			}
		}
	}
	return frequency_vector;
}


int** Algorithm::get_sorted_frequency_vector(int** frequency_vector,int* sort_order) {
	const auto row_size = sizeof(*frequency_vector) / sizeof(int*);
	const auto col_size = sizeof(**frequency_vector) / sizeof(int*);
	int** sorted_freq = new int* [row_size];

	for (auto i = 0; i < row_size; ++i) sorted_freq[i] = new int[col_size];

	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			sorted_freq[i][j] = frequency_vector[sort_order[i]][sort_order[j]];
		}
	}
	return sorted_freq;
}


bool Algorithm::main_procedure()
{
	const auto row_size = sizeof(*sorted_frequency_a) / sizeof(int*);
	const auto col_size = sizeof(**sorted_frequency_a) / sizeof(int**);

	if (!equals(sorted_frequency_b, sorted_frequency_b, row_size, col_size)) return false;
	return swap_procedure();
}