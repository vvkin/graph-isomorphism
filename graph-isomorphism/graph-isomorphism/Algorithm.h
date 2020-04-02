#include "Graph.h"
#include "Structures.h"

class Algorithm
{
private:
	static bfs_result bfs(Graph&, int);
	template<typename T>
	static T* create_a(T, int);
	static element** get_sign_matrix(Graph&);
};





