#include "Graph.h"
#include "Parser.h"
#include "Algorithm.h"
#include "Structures.h"

template<typename T>
void print_array(T* array, const int size) {
	for (auto i = 0; i < size; ++i) {
		cout << array[i] << ", ";
	} cout << endl;
}

template<typename T>
void print_vector_array(vector<T>* array, const int size) {
	for (auto i = 0; i < size; ++i) {
		for (auto& element : array[i]) {
			cout << element + 1 << ", ";
		} cout << endl;
	} cout << endl;
}

std::ostream& operator<<(std::ostream& out, const element& e) {
	out << (e.sign == sign::plus ? "+" : "-") << e.distance
		<< "." << e.vertices << "." << e.edges;
	return out;
}

void print_matrix(element** matrix, const int size) {
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			cout << setw(8) << matrix[i][j];
		} cout << endl;
	} cout << endl;
}

int main() {
	auto graph = Parser::parse("graph_a.txt");
	auto new_graph = graph.delete_edge(0, 1);
	const auto result_1 = Algorithm::bfs(graph, 0);
	const auto result_2 = Algorithm::bfs(graph, 1);
	print_array(result_1.distance, 8);
	print_vector_array(result_1.path, 8);
	print_array(result_2.distance, 8);
	print_vector_array(result_2.path, 8);
	const auto matrix = Algorithm::get_sign_matrix(graph);
	print_matrix(matrix, 8);
}