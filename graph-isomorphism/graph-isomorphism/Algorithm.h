#include "Graph.h"
#include "Structures.h"

class Algorithm{
public:
	static bfs_result bfs(Graph&, int);
	template<typename T>
	static T* create_a(T, int);
	static element** get_sign_matrix(Graph&);
	static bool is_isomorphic(Graph&, Graph&);
	static std::vector<element> get_lexicographical_order(Graph&);
private:
};





