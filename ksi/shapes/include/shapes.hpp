#ifndef _SHAPES_SHAPES_H_
#define _SHAPES_SHAPES_H_

#include <memory>
#include <vector>

#include "../lib/shape.hpp"
#include "../lib/cube.hpp"
#include "../lib/cuboid.hpp"
#include "../lib/cylinder.hpp"
#include "../lib/pyramid.hpp"

namespace shapes {

	typedef std::unique_ptr<shape>(*make_shape_f)(const std::vector<double> &);

};	//-- namespace shapes --

#endif //-- _SHAPES_SHAPES_H_ --
