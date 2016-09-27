#include "pyramid.h"

namespace shapes {

    std::unique_ptr<shape>
    make_pyramid(const std::vector<double>& sides, const std::vector<double>& angles, double hight, double tolerance) {
        unsigned sideNumber = std::min(sides.size(), angles.size());
        double
            cumulativeAngle = 0,
            xAxis = 0,
            yAxis = 0;

        for (unsigned k = 0; k < sideNumber; ++k) {
            xAxis += sides[k] * cos(cumulativeAngle);
            yAxis += sides[k] * sin(cumulativeAngle);
            unsigned angleIndex = (k == sideNumber - 1) ? 0 : k + 1;
            cumulativeAngle += M_PI - angles[angleIndex];
        }

        if (sqrt(xAxis * xAxis + yAxis * yAxis) > tolerance)
            throw std::invalid_argument("Unclosed base!");
        else {
            polygon poly(sideNumber, sides, angles);
            return std::unique_ptr<shape>(new pyramid(poly, hight));
        }
    };

	std::unique_ptr<shape>
	make_pyramid_grad(const std::vector<double> &sides, const std::vector<double> &anglesGrad, double height, double tolerance) {
		std::vector<double> anglesRad(anglesGrad.size());
		std::transform(anglesGrad.cbegin(), anglesGrad.cend(), anglesRad.begin(), [](double angle) -> double {return angle / 180.0 * M_PI;});
		return make_pyramid(sides, anglesRad, height, tolerance);
	}

    std::unique_ptr<shape>
    make_pyramid(const std::vector<double> &args) {
		args_check<pyramid, 7>(args);
		//-- s, s, ..... , a, a, ... , h, t = 1e-6 --
		std::size_t angleNumber = (args.size() - 1) / 2;
		auto it = args.cbegin();
		std::vector<double> sides(it, it + angleNumber);
		it += angleNumber;
		std::vector<double> angles(it, it + angleNumber);
		it += angleNumber;
		double height = *it;
		double tolerance = 1e-6;
		if (it + 1 != args.cend())
			tolerance = *(it + 1);
		return make_pyramid_grad(sides, angles, height, tolerance);
    };

    polygon::polygon(unsigned sideNumber, const std::vector<double>& sides, const std::vector<double> &angles) :
        mSideNumber(sideNumber),
        mSides(sides.cbegin(), sides.cbegin() + sideNumber),
        mAngles(angles.cbegin(), angles.cbegin() + sideNumber)
    {};

    polygon::polygon(const polygon& other) :
        mSideNumber(other.side_number()),
        mSides(other.sides()),
        mAngles(other.angles())
    {};

    double
    polygon::area() const {
        double angle_k = angles()[side_number() - 1];
        double side_0k = sides()[side_number() - 1];
        double area = 0;
        for (std::size_t k = side_number() - 1; k >= 2; --k) {
            area += 0.5 * side_0k * sides()[k - 1] * sin(angle_k);
            //-- Cos formula --
            double nextSide_0k = sqrt(side_0k * side_0k + sides()[k - 1] * sides()[k - 1] - 2.0 * cos(angle_k) * side_0k * sides()[k - 1]);
            //-- Sin formula --
            double triangleAngle_k_1 = asin(sin(angle_k) / nextSide_0k * side_0k);

            side_0k = nextSide_0k;
            angle_k = angles()[k - 1] - triangleAngle_k_1;
        }
        return area;
    };

    std::string
    polygon::to_string() const {
        std::stringstream ss;
        ss << "polygon : {";
        for (std::size_t k = 0; k < side_number(); ++k) {
            std::size_t a = k;
            std::size_t b = (k == side_number() - 1)? 0 : k + 1;
            ss << "L{" << a << "-" << b << " : " << sides()[a] << "}, " << "A{" << b << " : " << angles()[b] << "}";
            if (k != side_number() - 1)
                ss << ", ";
        }
        ss << "}";
        return ss.str();
    };

    unsigned
    polygon::side_number() const {
        return mSideNumber;
    };
    const std::vector<double>&
    polygon::sides() const {
        return mSides;
    };
    const std::vector<double>&
    polygon::angles() const {
        return mAngles;
    };

    pyramid::pyramid(const polygon& polygon, double height) :
        shape(),
        mPolygon(polygon),
        mHeight(height)
    {};

    pyramid::pyramid(const pyramid& other) :
        shape(),
        mPolygon(other.poly()),
        mHeight(other.mHeight)
    {};

    double
    pyramid::volume() const {
        return (1.0/3.0) * poly().area() * height();
    };

    std::string
    pyramid::to_string() const {
        std::stringstream ss;
        ss << "pyramid : ";
        ss << "{";
        ss << poly().to_string() << ", " << "H{" << height() << "}" << ", V{" << volume() << "}";
        ss << "}";
        return ss.str();
    };

    const polygon&
    pyramid::poly() const {
        return mPolygon;
    };

    double
    pyramid::height() const {
        return mHeight;
    };

};  //-- namespace shapes --



























