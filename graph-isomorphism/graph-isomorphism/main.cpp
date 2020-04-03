#include "Graph.h"
#include "Parser.h"
#include "Algorithm.h"
#include "Printer.h"


int main() {
	auto graph = Parser::parse("graph_a.txt");
	auto new_graph = graph.delete_edge(3, 0);
	new_graph.get_info();
	const auto result_1 = Algorithm::bfs(new_graph, 3);
	const auto result_2 = Algorithm::bfs(new_graph, 0);
	Printer::print_array(result_1.distance, 8);
	Printer::print_vector_array(result_1.path, 8);
	Printer::print_array(result_2.distance, 8);
	Printer::print_vector_array(result_2.path, 8);
	const auto matrix = Algorithm::get_sign_matrix(graph);
	Printer::print_matrix(matrix, 8);

	auto unique_el = Algorithm::get_lexicographical_order(graph);
	Printer::print_vector(unique_el);
	cout << unique_el.size();
}