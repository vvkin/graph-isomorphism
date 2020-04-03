#pragma once
#include <vector>
#include "Structures.h"

class Printer {
public:
	template<typename T>
	static void print_vector_array(std::vector<T>*,const int);
	template<typename T>
	static void print_array(T*, const int);
	static void print_matrix(element**, const int);
	template<typename T>
	static void print_vector(vector<T>);
};

inline std::ostream& operator<<(std::ostream& out, const element& e) { //I don`t understand why, but without INLINE this method doesn`t work :)
	out << (e.sign == sign::plus ? "+" : "-") << e.distance
		<< "." << e.vertices << "." << e.edges;
	return out;
}

template<typename T>
inline void Printer::print_vector_array(std::vector<T>* array, const int size) {
	for (auto i = 0; i < size; ++i) {
		for (auto& element : array[i]) {
			cout << element + 1 << ", ";
		} cout << endl;
	} cout << endl;
}

template<typename T>
inline void Printer::print_array(T* array, const int size) {
	for (auto i = 0; i < size; ++i) {
		cout << array[i] << ", ";
	} cout << endl;
}

template<typename T>
inline void Printer::print_vector(vector<T> vec)
{
	for (auto& el : vec) {
		cout << el << " ";
	}
	cout << "\n";
}

inline void Printer::print_matrix(element** matrix, const int size) {
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			cout << setw(8) << matrix[i][j];
		} cout << endl;
	} cout << endl;
}