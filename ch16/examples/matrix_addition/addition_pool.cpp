#include <utility>
#include <future>
#include <examples/common.h>

#include "../common.h"
#include "../../multiprocessing/RealThreadPool.h"
class MatrixView {
public:
	Matrix &m;
	const size_t row, col, n;

	MatrixView(Matrix &_m, size_t _row, size_t _col, size_t _n) : m(_m), row(_row), col(_col), n(_n) {}
	explicit MatrixView(Matrix &_m) : m(_m), row(0), col(0), n(m.size()) {}

	double &get(const int x, const int y) {
		return m[row + x][col + y];
	}

	Array2<MatrixView> split() {
		Array2<MatrixView> result;
		size_t newSize = n / 2;
		result.resize(2);
		result[0].emplace_back(m, row, col, newSize);
		result[0].emplace_back(m, row, col + newSize, newSize);
		result[1].emplace_back(m, row + newSize, col, newSize);
		result[1].emplace_back(m, row + newSize, col + newSize, newSize);
		return result;
	}

	~MatrixView() {}
};

int THRESHOLD = 128;
/**
4096
Execution duration: 336548us
Execution duration: 336.548ms
Execution duration: 0.336548s
 */
class MatrixTask {
public:

	static void add(MatrixView &a, MatrixView &b, MatrixView &c) {
		if (a.n <= THRESHOLD) {
			for (int i = 0; i < a.n; i++) {
				for (int j = 0; j < b.n; j++) {
					c.get(i, j) = a.get(i, j) + b.get(i, j);
				}
			}
		} else {
			auto aa = a.split(), bb = b.split(), cc = c.split();
			Array2<std::future<void>> futures(2);
			for (size_t i = 0; i < 2; i++) {
				futures[i].push_back(std::async(std::launch::async, [i, &aa, &bb, &cc]{ MatrixTask::add(aa[i][0], bb[i][0], cc[i][0]); }));
				futures[i].push_back(std::async(std::launch::async, [i, &aa, &bb, &cc]{ MatrixTask::add(aa[i][1], bb[i][1], cc[i][1]); }));
			}
			for (size_t i = 0; i < 2; i++) {
				for (size_t j = 0; j < 2; j++) {
					futures[i][j].get();
				}
			}
		}
	}
};

/**
 * 2048 ~ DNF
 * @return
 */
int main() {
	START_CHRONO
	auto ma = randomMatrix(N_ADD);
	auto mb = randomMatrix(N_ADD);
	auto mc = randomMatrix(N_ADD);
	MatrixView a(ma), b(mb), c(mc);
	MatrixTask::add(a, b, c);
	END_CHRONO
	return 0;
}
