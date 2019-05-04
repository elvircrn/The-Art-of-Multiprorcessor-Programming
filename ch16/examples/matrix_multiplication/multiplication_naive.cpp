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
		workers.resize(n);
		for (int i = 0; i < n; i++) {
			workers[i].resize(n);
			for (int j = 0; j < n; j++) {
				workers[i][j] = std::thread(&MMThread::calculate, this, i, j);
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				workers[i][j].join();
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
 * Execution duration: 1.27312e+06us
 * Execution duration: 1273.12ms
 * Execution duration: 1.0566e+06us
 * Execution duration: 1056.6ms
 * Execution duration: 1.18257e+06us
 * Execution duration: 1182.57ms
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