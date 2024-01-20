#ifndef IS_GEOMETRY_H
#define IS_GEOMETRY_H

#include "core/variant/variant.h"
#include "modules/iota/templates/static_vector.h"

class ISGeometry {
public:
	StaticVector<Rect2i, 4> split_rect(const Rect2i &rect, const Point2i &point) {
		Size2i pos_diff = point - rect.position;
		Size2i end_diff = rect.size - pos_diff;
		bool split_x = pos_diff.x > 0 && end_diff.x > 0;
		bool split_y = pos_diff.y > 0 && end_diff.y > 0;
		enum SplitContent {
			SPLIT_NONE = 0b00,
			SPLIT_X = 0b01,
			SPLIT_Y = 0b10,
			SPLIT_XY = 0b11
		} content = SplitContent(SPLIT_X * split_x + SPLIT_Y * split_y);
		switch (content) {
			case SPLIT_X:
				return { Rect2i(rect.position, { pos_diff.x, rect.size.y }), Rect2i(point.x, rect.position.y, end_diff.x, rect.size.y) };
			case SPLIT_Y:
				return { Rect2i(rect.position, { rect.size.x, pos_diff.y }), Rect2i(rect.position.x, point.y, rect.size.x, end_diff.y) };
			case SPLIT_XY:
				return {
					Rect2i(rect.position, pos_diff), Rect2i(point, end_diff),
					Rect2i(point.x, rect.position.y, end_diff.x, pos_diff.y),
					Rect2i(rect.position.x, point.y, pos_diff.x, end_diff.y)
				};
		}
		return { rect };
	}

	StaticVector<Rect2i, 4> clip_rect(const Rect2i &rect_a, const Rect2i &rect_b) {
		StaticVector<Rect2i, 4> result;
		Point2i rect0_end = rect_a.get_end();
		Point2i rect1_end = rect_b.get_end();
		Size2i pos_diff = rect_b.position - rect_a.position;
		Size2i end_diff = rect0_end - rect1_end;
		if (pos_diff.width > 0)
			result.emplace_back(rect_a.position, Size2i(pos_diff.width, rect_a.size.height));
		if (pos_diff.height > 0)
			result.emplace_back(rect_b.position.x, rect_a.position.y, rect_b.size.width, pos_diff.height);
		if (end_diff.width > 0)
			result.emplace_back(rect1_end.x, rect_a.position.y, end_diff.width, rect_a.size.height);
		if (end_diff.height > 0)
			result.emplace_back(rect_b.position.x, rect1_end.y, rect_b.size.width, end_diff.height);
		return result;
	}
};

#endif
