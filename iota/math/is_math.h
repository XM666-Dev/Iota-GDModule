#ifndef IS_MATH_H
#define IS_MATH_H

#include "core/variant/variant.h"

class ISMath {
public:
	template <class T>
	static T floor_divide(const T &a, const T &b) {
		return a / b - (a % b < 0);
	}

	template <class T>
	static T floor_modulo(const T &a, const T &b) {
		return a % b + b * (a % b < 0);
	}

	static Vector2i floor_divide(const Vector2i &a, const Vector2i &b) {
		return { floor_divide(a.x, b.x), floor_divide(a.y, b.y) };
	}

	static Vector2i floor_modulo(const Vector2i &a, const Vector2i &b) {
		return { floor_modulo(a.x, b.x), floor_modulo(a.y, b.y) };
	}
};

#endif
