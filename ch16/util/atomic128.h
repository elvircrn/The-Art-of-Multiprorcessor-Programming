#ifndef CH16_CASH128_H
#define CH16_CASH128_H

#include "bitutil.h"

#include <cassert>
#include <cstdint>
#include <cstdio>

#include <thread>
#include <atomic>

// GCC seems to have second thoughts about inlining the list push/pop functions, even at -O3...
#define ALWAYS_INLINE __attribute__((__always_inline__))

namespace cas {

ALWAYS_INLINE int toBuiltInMemOrder(std::memory_order order) {
	switch (order) {
	case std::memory_order_relaxed : return __ATOMIC_RELAXED;
	case std::memory_order_consume : return __ATOMIC_CONSUME;
	case std::memory_order_acquire : return __ATOMIC_ACQUIRE;
	case std::memory_order_release : return __ATOMIC_RELEASE;
	case std::memory_order_acq_rel : return __ATOMIC_ACQ_REL;
	case std::memory_order_seq_cst : return __ATOMIC_SEQ_CST;
	default                        : assert(false);
		return 0;
	}
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
ALWAYS_INLINE bool cas128(volatile uint128 *destination,
													uint128 *expected,
													uint128 desired,
													std::memory_order successMemOrder,
													std::memory_order failureMemOrder) {
	constexpr bool weak = true;
	return __atomic_compare_exchange_n(destination, expected, desired, weak,
																		 toBuiltInMemOrder(successMemOrder),
																		 toBuiltInMemOrder(failureMemOrder));
}
#pragma clang diagnostic pop
}

using AtomicStampedRef64 = std::atomic<uint128>;

inline uint64 getVal(const AtomicStampedRef64 &ref) {
	return static_cast<uint64>((ref.load()) >> 64ULL);
}

inline uint64 getStamp(const AtomicStampedRef64 &ref) {
	return static_cast<uint64>(ref.load());
}

inline std::pair<uint64, uint64> get(const AtomicStampedRef64 &ref) {
	uint128 latch = ref.load();

	return {latch >> static_cast<uint128>(64), latch & ((static_cast<uint128>(1) << static_cast<uint128>(64)) - 1)};
}

inline uint128 createStampedValue(const uint64 &val, const uint64 &stamp) {
	return static_cast<uint128>(((static_cast<uint128>(val) << static_cast<uint128>(64))) + stamp);
}


static char *qtoa(uint128 n) {
	static char buf[40];
	unsigned int i, j, m = 39;
	memset(buf, 0, 40);
	for (i = 128; i-- > 0;) {
		int carry = !!(n & ((uint128) 1 << i));
		for (j = 39; j-- > m + 1 || carry;) {
			int d = 2 * buf[j] + carry;
			carry = d > 9;
			buf[j] = carry ? d - 10 : d;
		}
		m = j;
	}
	for (i = 0; i < 38; i++) {
		if (buf[i]) {
			break;
		}
	}
	for (j = i; j < 39; j++) {
		buf[j] += '0';
	}
	return buf + i;
}



#endif //CH16_CASH128_H
