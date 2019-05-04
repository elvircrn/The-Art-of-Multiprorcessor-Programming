#include "common.h"


// 3000 ~ 124ms
/**
 * 4096
Execution duration: 428477us
Execution duration: 428.477ms
Execution duration: 0.428477s

 * @return
 */
int main() {
	START_CHRONO

	auto a = randomMatrix(N_ADD);
	auto b = randomMatrix(N_ADD);
	auto c = randomMatrix(N_ADD);

	for (size_t i = 0; i < N_ADD; i++) {
		for (size_t j = 0; j < N_ADD; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}

	std::cout << c[0][0] << 'n';

	END_CHRONO
	return 0;
}