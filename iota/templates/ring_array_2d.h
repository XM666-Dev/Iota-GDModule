#ifndef RING_BUFFER_2D_H
#define RING_BUFFER_2D_H

#include "core/variant/variant.h"
#include "modules/iota/math/is_geometry.h"
#include "modules/iota/math/is_math.h"

template <typename T>
class RingArray2D {
private:
	Vector<T> data;
	Rect2i region;

public:
	T &operator[](const Vector2i &index) {
		Vector2i local_index = ISMath::floor_modulo(index, region.size);
		return data[local_index.y * region.size.width + local_index.x];
	}

	const Rect2i &get_region() {
		return region;
	}

	void resize(const Vector2i &new_size) {
		region.size = new_size;
		data.resize(region.get_area());
	}

	void reshape(const Rect2i &new_region) {
		ERR_FAIL_COND(new_region.get_area() != region.get_area());
		region = new_region;
	}

	StaticVector<Rect2i, 4> get_uninitialized_region(const Rect2i &new_region) {
		return ISGeometry::clip_rect(region, new_region);
	}
};

#endif
