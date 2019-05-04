#include <utility>

#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <thread>

#include "common.h"

class MMThread {
public:
	Matrix a, b, c;
	size_t n;
	Array2<std::thread> workers;

	MMThread(Matrix _a, Matrix _b, Matrix _c) : a(std::move(_a)), b(std::move(_b)), c(std::move(_c)) {
		n = a.size();
	}

	void multiply() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				calculate(this, i, j);
			}
		}
	}

	static void calculate(MMThread *_this, int i, int j) {
		double dotProduct = 0.0;
		for (int k = 0; k < _this->n; k++) {
			dotProduct += _this->a[i][k] * _this->b[k][j];
		}
		_this->c[i][j] = dotProduct;
	}
};

/**
 * Execution duration: 7206.46us
 * Execution duration: 7.20646ms
 * Execution duration: 7020.12us
 * Execution duration: 7.02012ms
 * @return
 */
int main() {
	START_CHRONO

	try {
		auto mm = MMThread{randomMatrix(N), randomMatrix(N), randomMatrix(N)};

		mm.multiply();
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	END_CHRONO

	return 0;
}