#include "cuboid.hpp"

namespace shapes {

    std::unique_ptr<shape>
    make_cuboid(double length, double height, double width) {
        return std::unique_ptr<shape>(new cuboid(length, height, width));
    };

	std::unique_ptr<shape>
	make_cuboid(const std::vector<double> &args) {
		args_check<cuboid, 3>(args);
		return make_cuboid(args[0], args[1], args[2]);
	};

    cuboid::cuboid(double length, double height, double width) :
        mLength(length),
        mHeight(height),
        mWidth(width)
    {};

    cuboid::cuboid(const cuboid& other) :
        mLength(other.length()),
        mHeight(other.height()),
        mWidth(other.width())
    {};

    double
    cuboid::volume() const {
        return length() * height() * width();
    };

    std::string
    cuboid::to_string() const {
        std::stringstream ss;
        ss << "cuboid : ";
        ss << "{" << length() << ", " << height() << ", " << width() << "}";
        return ss.str();
    };

    double
    cuboid::length() const {
        return mLength;
    };

    double
    cuboid::height() const {
        return mHeight;
    };

    double
    cuboid::width() const {
        return mWidth;
    };

};  //-- namespace shapes --
