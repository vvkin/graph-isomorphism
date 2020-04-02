#pragma once

struct Edge {
	int in;
	int out;
};

class Graph {
private:
	Edge* edges_list;
	int vertices_num;
	int edges_num;

public:
	Graph(int, int, Edge*);
	~Graph();
	Graph delete_edge(int, int);
	void get_info();
};

