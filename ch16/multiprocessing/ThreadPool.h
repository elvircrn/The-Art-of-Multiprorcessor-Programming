#include "BDequeue.h"

#include "examples/common.h"
#include <iostream>
#include <thread>
#include <random>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using bde::BDequeue;


using ll = long long;

namespace random_util {
class RandomGenerator {
private:
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> dis;

public:
	RandomGenerator(const int low, const int high) {
		dis = std::uniform_int_distribution(low, high - 1);
		gen = std::mt19937(rd());
	}

	int operator()() {
		return dis(gen);
	}

	inline std::uniform_int_distribution<int> &getDis() {
		return dis;
	}

	inline auto &getGen() {
		return gen;
	}

	inline auto &getRd() {
		return rd;
	}
};
auto getDefaultRandomDevice() {
	unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
	return std::default_random_engine(seed);
}

}

using namespace random_util;

using Runnable = std::function<void()>;
template<class T = Runnable, typename = EnableIf<std::is_invocable<T>>>
class ExecutorService {
	const size_t _count{std::thread::hardware_concurrency()};
	std::vector<BDequeue<T>> _queues;
	std::vector<std::thread> _threads;
	std::atomic<size_t> _index{0};

	void run(size_t me) {
		RandomGenerator nextTarget(0, _count);
		for (;;) {
			if (auto taskMaybe = _queues[me].popBottom()) {
				(*taskMaybe)();
			}

			std::this_thread::yield();

			auto target = nextTarget();

			if (auto taskMaybe = _queues[target].popBottom()) {
				(*taskMaybe)();
			}
		}
	}

public:
	ExecutorService() {
		_queues.resize(_count);
		for (unsigned i = 0; i < _count; i++) {
			_threads.emplace_back([&, i]() {
				run(i);
			});
		}
	}

	~ExecutorService() {
		for (auto &t : _threads) {
			t.join();
		}
	}

	void async(T &&f) {
		_queues[_index++ % _count].pushBottom(std::forward<T>(f));
	}
};

