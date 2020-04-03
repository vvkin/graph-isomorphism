#include "Graph.h"
#include "Parser.h"
#include "Algorithm.h"
#include "Printer.h"


int main() {
	auto graph_a = Parser::parse("graph_a.txt");
	auto graph_b = Parser::parse("graph_b.txt");
	const auto matrix_a = Algorithm::get_sign_matrix(graph_a);
	const auto matrix_b = Algorithm::get_sign_matrix(graph_b);
	Printer::print_matrix(matrix_a, 8,8);
	Printer::print_matrix(matrix_b, 8, 8);
	const auto unique_elements_a = Algorithm::get_lexicographical_order(graph_a);
	const auto unique_elements_b = Algorithm::get_lexicographical_order(graph_b);
	Printer::print_vector(unique_elements_a);
	Printer::print_vector(unique_elements_b);
	auto* sort_order_a = Algorithm::get_sort_order(graph_a);
	auto* sort_order_b = Algorithm::get_sort_order(graph_b);
	Printer::print_array(sort_order_a, 8);
	Printer::print_array(sort_order_b, 8);
	auto** sorted_sign_m_a = Algorithm::get_canonical_form(graph_a);
	auto** sorted_sign_m_b = Algorithm::get_canonical_form(graph_b);
	Printer::print_matrix(sorted_sign_m_a, 8, 8);
	Printer::print_matrix(sorted_sign_m_b, 8, 8);
	Algorithm::swap_procedure(graph_a, graph_b);
}