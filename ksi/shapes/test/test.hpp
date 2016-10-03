#include <initializer_list>

#include "../include/shapes.hpp"

template<typename T>
struct test_shape {
    using shape_type = T;
	static int cloning(std::initializer_list<double> args) {
		auto shape = shapes::make_shape<shape_type>::factory(args);
		auto shapeClone = shape->clone();
		return 0;
	};
};

int test_all() {
	test_shape<shapes::cylinder>::cloning({ 1, 3 });
	test_shape<shapes::cuboid>::cloning({ 2, 3, 4 });
	test_shape<shapes::cube>::cloning({ 5 });
	test_shape<shapes::pyramid>::cloning({ 1, 1, 1, 60, 60, 60, 1 });
	return 0;
};



