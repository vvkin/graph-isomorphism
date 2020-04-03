#include "Graph.h"
#include "Structures.h"

class Algorithm{
public:
	Algorithm(Graph&, Graph&);
	bool is_isomorphic();
 
private:
	int** get_sorted_frequency_vector(int**, int*, int);
	bool main_procedure();
	template<typename T>
	static T* create_a(T, int);
	int** get_frequency_vector(std::vector<element>, element**);
	static bfs_result bfs(Graph&, int);
	static element** get_sign_matrix(Graph&);
	bool swap_procedure();
	int* get_sort_order(int**, int);
	element** get_canonical_form(int*, element**);
	std::vector<element> get_lexicographical_order(element**);

	//
	Graph a;
	Graph b;
	int size;
	int** frequency_vector_a;
	int** frequency_vector_b;
	int** sorted_frequency_a;
	int** sorted_frequency_b;
	int* sort_order_a;
	int* sort_order_b;
	int unique_a_size;
	int unique_b_size;
	element** canon_m_a;
	element** canon_m_b;
	element** sign_m_a;
	element** sign_m_b;


};





