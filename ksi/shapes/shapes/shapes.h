#ifndef _SHAPES_SHAPES_H_
#define _SHAPES_SHAPES_H_

#include <memory>
#include <vector>

#include "shape.h"
#include "cube.h"
#include "cuboid.h"
#include "cylinder.h"
#include "pyramid.h"

namespace shapes {

	typedef std::unique_ptr<shape>(*make_shape_f)(const std::vector<double> &);

};	//-- namespace shapes --

#endif //-- _SHAPES_SHAPES_H_ --
