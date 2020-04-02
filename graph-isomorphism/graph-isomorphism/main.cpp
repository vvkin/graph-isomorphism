#include <iostream>
#include "Graph.h"
#include "Parser.h"

int main() {
	Graph newgraph = Parser::parse("graph_a.txt");
	newgraph.get_info();
	auto gg = newgraph.delete_edge(1, 2);
	gg.get_info();
}