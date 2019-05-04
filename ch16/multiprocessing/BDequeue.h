#include <functional>
#include <vector>
#include <atomic>
#include <optional>
#include <wmmintrin.h>
#include <type_traits>
#include <array>
#include "examples/common.h"
#include "../util/atomic128.h"

/**
 * Bounded work-stealing  dequeue. popBottom()  and pushBottom() are  only called
 * by the owner threads. Thieves never call these methods - they only  use popTop.
 * Therefore, in order to optimize for the common case, we need to make popBottom
 * and pushBottom fast.
 */
namespace bde {
template<class T, typename = EnableIf<std::is_invocable<T>>>
class BDequeue {
	std::vector<T> tasks{128};
	AtomicStampedRef64 top{0};
	std::atomic<uint32> bottom{0};

public:

	BDequeue() = default;

	explicit BDequeue(const BDequeue<T>& queue) {
		tasks = queue.tasks;
		top.store(top.load());
		bottom.store(bottom.load());
	}

	BDequeue& operator=(const BDequeue<T> &queue) {
		if (this == &queue) {
			return *this;
		}
		tasks = queue.tasks;
		top.store(queue.load());
		bottom.store(queue.load());
		return *this;
	}

	bool isEmpty() {
		auto localTopVal = getVal(top);
		auto localBottomVal = bottom.load();
		return localBottomVal <= localTopVal;
	}

	/**
	 * Used by owners to retrieve tasks.
	 * @return Possibly, a task.
	 */
	std::optional<T> popBottom() {
		// There is nothing in the queue, should this be isEmpty()?
		if (bottom == 0) {
			return {};
		}

		auto task = tasks[--bottom]; // Prepare to grab the bottom task

		auto oldTop = top.load();
		auto oldTopValue = getVal(oldTop);
		uint64 newTopVal = 0, newStamp = getStamp(oldTop) + 1; // Read and prepare new values

		// No conflict, bottom and top are more than one apart
		if (bottom > oldTopValue) {
			return task;
		}

		// At most one item left
		if (bottom == oldTopValue) {
			bottom.store(0);
			auto newTop = createStampedValue(newTopVal, newStamp);
			if (cas::cas128(&oldTop, &newTop, oldTop, std::memory_order_seq_cst, std::memory_order_seq_cst)) {
				return task;
			}
		}

		top.store(createStampedValue(newTopVal, newStamp));

		return tasks[bottom];
	}

	/**
	 * Used by owners to add tasks to the queue.
	 * @param task
	 */
	void pushBottom(T &&task) {
		tasks[bottom++] = std::move(task);
	}

	/**
	 * Used by thiefs to retrieve tasks.
	 * @return Task
	 */
	std::optional<T> popTop() {
		auto oldTop = top.load();
		auto[oldTopVal, oldTopStamp] = get(oldTop);
		auto newTopStamp = oldTopStamp + 1;
		auto newTopVal = oldTopVal + 1;

		if (bottom <= oldTopVal) {
			return {};
		}

		auto task = tasks[oldTopVal];

		auto newTop = createStampedValue(newTopVal, newTopStamp);

		if (top.compare_exchange_strong(oldTop, newTop)) {
			return task;
		}

		return {};
	}
};
}

