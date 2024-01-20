#ifndef STATIC_ARRAY_2D_H
#define STATIC_ARRAY_2D_H

#include "core/variant/variant.h"

template <class T, size_t Width, size_t Height>
class StaticArray2D {
public:
	T data[Height][Width];

	T &operator[](const Vector2 &index) {
		return data[index.y][index.x];
	}
};

#endif
