#ifndef IS_MEMORY_H
#define IS_MEMORY_H

#include <cstddef>

class ISMemory {
public:
	template <class T, class... Args>
	static void construct_at(T *location, const Args &...args) {
		new (location) T(args...);
	}

	template <class T>
	static void destroy_at(T *location) {
		location->~T();
	}

	template <class T, class... Args>
	static void uninitialized_copy_v(T *result, const Args &...args) {
		(construct_at(result++, args), ...);
	}

	template <class T, class... Args>
	static void uninitialized_copy_n(T *first, size_t count, T *result) {
		for (T *last = first + count; first < last; ++first, ++result) {
			construct_at(first, result);
		}
	}

	template <class T>
	static void destroy_n(T *first, size_t count) {
		for (T *last = first + count; first < last; ++first) {
			destroy_at(first);
		}
	}
};

#endif
