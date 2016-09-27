#ifndef _SHAPES_CYLINDER_H_
#define _SHAPES_CYLINDER_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include <sstream>

#include "shape.h"
#include "cloning.h"

namespace shapes {

    std::unique_ptr<shape>
    make_cylinder(double radius, double height);

	std::unique_ptr<shape>
	make_cylinder(const std::vector<double> &args);

    class cylinder :
        public shape,
        public cloning::cloner<cylinder, shape>
    {
        public:
            friend std::unique_ptr<shape>
            make_cylinder(double, double);

            cylinder(const cylinder& other);

            virtual ~cylinder() override {};

            virtual double
            volume() const override;

            virtual std::string
            to_string() const override;

            inline double radius() const;
            inline double height() const;

        protected:
            cylinder(double radius, double height);

        private:
            double mRadius;
            double mHeight;
    };

};  //-- namespace shapes --
#endif // _SHAPES_CYLINDER_H_
