#include "cylinder.h"

namespace shapes {

    std::unique_ptr<shape>
    make_cylinder(double radius, double height) {
        return std::unique_ptr<shape>(new cylinder(radius, height));
    };

	std::unique_ptr<shape>
	make_cylinder(const std::vector<double> &args) {
		args_check<cylinder, 2>(args);
		return make_cylinder(args[0], args[1]);
	};

    cylinder::cylinder(double radius, double height) :
        mRadius(radius),
        mHeight(height)
    {};

    cylinder::cylinder(const cylinder& other) :
        mRadius(other.radius()),
        mHeight(other.height())
    {};

    double
    cylinder::volume() const {
        return M_PI * radius() * radius();
    };

    std::string
    cylinder::to_string() const {
        std::stringstream ss;
        ss << "cylinder : ";
        ss << "{" << radius() << ", " << height() << "}";
        return ss.str();
    };

    double
    cylinder::radius() const {
        return mRadius;
    };

    double
    cylinder::height() const {
        return mHeight;
    };

};  //-- namespace shapes --
