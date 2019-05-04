#ifndef CH16_CONSTANTS_H
#define CH16_CONSTANTS_H
#include <vector>
#include <chrono>
#include <iostream>


template<typename T>
using Invoke = typename T::type;

template<typename Condition>
using EnableIf = Invoke<std::enable_if<Condition::value>>;


template<class T>
using Array2 = std::vector<std::vector<T>>;

using Matrix = Array2<double>;

Matrix randomMatrix(size_t n) {
	Matrix m(n, std::vector<double>(n, 0));
	return m;
}

void printMatrix(const Matrix &m) {
	for (const auto& row : m) {
		for (const auto& val : row) {
			std::cout << val << ' ';
		}
		std::cout << '\n';
	}
}

#define N 1000
#define N_ADD 4096

#define START_CHRONO auto start = std::chrono::steady_clock::now();

#define END_CHRONO \
auto end = std::chrono::steady_clock::now(); \
auto diff = end - start; \
std::cout << "Execution duration: " << std::chrono::duration <double, std::micro> (diff).count() << "us\n"; \
std::cout << "Execution duration: " << std::chrono::duration <double, std::milli> (diff).count() << "ms\n"; \
std::cout << "Execution duration: " << std::chrono::duration <double> (diff).count() << "s\n";

#endif //CH16_CONSTANTS_H
