#ifndef CH2_PETERSON_LOCK_H
#define CH2_PETERSON_LOCK_H

#include <atomic>
#include <thread>
#include <vector>

class PetersonLock {
private:
	std::atomic<int> flags[2] = { {}, {} };
	std::atomic<int> turn;

public:
	// Indexed by thread ID, 0 or 1
	void lock(unsigned me) {
		unsigned he = 1 - me;
		flags[me].store(1, std::memory_order_relaxed);
		turn.exchange(he, std::memory_order_acq_rel);
		while (flags[he].load(std::memory_order_acquire) && he == turn.load(std::memory_order_relaxed)) {
			std::this_thread::yield();
		}
	}

	void unlock(unsigned index) {
		flags[index].store(0, std::memory_order_release);
	}
};

#endif //CH2_PETERSON_LOCK_H
