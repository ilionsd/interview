#ifndef _SHAPES_METAFACTORY_HPP_
#define _SHAPES_METAFACTORY_HPP_

#include <vector>
#include <memory>
#include <type_traits>

#include "shape.hpp"
#include "cylinder.hpp"
#include "cuboid.hpp"
#include "cube.hpp"
#include "pyramid.hpp"

namespace shapes {

	typedef std::unique_ptr<shape>(*make_shape_f)(const std::vector<double> &);

	template<typename T>
	struct make_shape {
		using type = T;
		static const make_shape_f factory;
	};

        template<>
	const make_shape_f make_shape<cylinder>::factory = &make_cylinder;
        template<>
	const make_shape_f make_shape<cube>::factory = &make_cube;
        template<>
	const make_shape_f make_shape<cuboid>::factory = &make_cuboid;
        template<>
	const make_shape_f make_shape<pyramid>::factory = &make_pyramid;
        
};	//-- namespace shapes --

#endif	//-- _SHAPES_METAFACTORY_HPP_ --
