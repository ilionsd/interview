#ifndef _SHAPES_SHAPE_H_
#define _SHAPES_SHAPE_H_

#include <iostream>
#include <string>
#include <vector>

#include "../include/cloning.hpp"

namespace shapes {

    class shape :
        public virtual cloning::cloneable<shape>
    {
        public:
            shape() = default;
            virtual ~shape() = default;

            virtual double
            volume() const = 0;

            virtual std::string
            to_string() const = 0;
    };

    inline std::ostream& operator<<(std::ostream& stream, const shape& obj) {
        stream << obj.to_string();
        return stream;
    };

	template<typename T, unsigned N>
	void args_check(const std::vector<double> &args) {
		if (args.size() < N)
			throw std::invalid_argument(std::string("Minimal args count to construct ") + typeid(T).name() + std::string(" is ") + std::to_string(N));
	};



};  //-- namespace shapes --

#endif // _SHAPES_SHAPE_H_
