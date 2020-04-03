#include "Graph.h"
#include "Structures.h"

class Algorithm{
public:
	static bfs_result bfs(Graph&, int);
	static element** get_sign_matrix(Graph&);
	static bool is_isomorphic(Graph&, Graph&);
	static std::vector<element> get_lexicographical_order(Graph&);
	static int* get_sort_order(Graph&);
	static element** get_canonical_form(Graph&);
private:
	static bool main_procedure(Graph&);
	void swap_procedure(Graph&, Graph&);
	template<typename T>
	static T* create_a(T, int);
	static int** get_frequency_vector(Graph&);
};





