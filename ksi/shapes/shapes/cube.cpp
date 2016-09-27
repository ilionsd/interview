#include "cube.h"

namespace shapes {

    std::unique_ptr<shape>
    make_cube(double side) {
        return std::unique_ptr<cube>(new cube(side));
    };

	std::unique_ptr<shape>
	make_cube(const std::vector<double> &args) {
		args_check<cube, 1>(args);
		return make_cube(args[0]);
	};

    cube::cube(double side) :
        mSide(side)
    {};

    cube::cube(const cube& other) :
        shape(),
        mSide(other.side())
    {};

    double
    cube::volume() const {
        return side() * side() * side();
    };

    std::string
    cube::to_string() const {
        std::stringstream ss;
        ss << "cube : ";
        ss << "{" << side() << ", " << side() << ", " << side() << "}";
        return ss.str();
    };

    double
    cube::side() const {
        return mSide;
    };

};  //-- namespace shapes --
