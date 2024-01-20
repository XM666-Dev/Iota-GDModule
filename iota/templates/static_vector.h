#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <modules/iota/os/is_memory.h>

template <class T, size_t Capacity>
class StaticVector {
public:
	size_t size;
	union {
		T data[Capacity];
	};

	StaticVector() :
			size() {}

	template <class... Args>
	StaticVector(const Args &...args) :
			size(sizeof...(args)) {
		ISMemory::uninitialized_copy_v(data, args...);
	}

	StaticVector(const StaticVector &other) :
			size(other.size) {
		ISMemory::uninitialized_copy_n(other.data, size, data);
	}

	~StaticVector() {
		ISMemory::destroy_n(data, size);
	}

	T *begin() {
		return data;
	}

	T *end() {
		return data + size;
	}

	T &operator[](size_t index) {
		return data[index];
	}

	template <class... Args>
	void emplace_back(const Args &...args) {
		ISMemory::construct_at(end(), args...);
		++size;
	}
};

#endif
