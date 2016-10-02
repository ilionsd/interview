#ifndef _SHAPES_PYRAMID_H_
#define _SHAPES_PYRAMID_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <sstream>

#include "shape.hpp"
#include "../include/cloning.hpp"

namespace shapes {

    std::unique_ptr<shape>
    make_pyramid(const std::vector<double> &sides, const std::vector<double> &angles, double height, double tolerance = 1e-6);

	std::unique_ptr<shape>
	make_pyramid_grad(const std::vector<double> &sides, const std::vector<double> &anglesGrad, double height, double tolerance = 1e-6);

    std::unique_ptr<shape>
    make_pyramid(const std::vector<double> &args);

    class polygon
    {
        public:
            friend std::unique_ptr<shape>
            make_pyramid(const std::vector<double> &, const std::vector<double> &, double, double);

            polygon(const polygon &other);

            std::string to_string() const;

            double area() const;

            inline unsigned side_number() const;
            inline const std::vector<double> &sides() const;
            inline const std::vector<double> &angles() const;

        protected:
            polygon(unsigned sideNumber, const std::vector<double> &sides, const std::vector<double> &angles);
            polygon(std::vector<double> &args);

        private:
            unsigned mSideNumber;
            std::vector<double> mSides;
            std::vector<double> mAngles;
    };

    class pyramid :
        public shape,
        public cloning::cloner<pyramid, shape>
    {
        public:
            friend std::unique_ptr<shape>
            make_pyramid(const std::vector<double>&, const std::vector<double>&, double, double);

            pyramid(const pyramid& other);

            virtual ~pyramid() override {};

            //-- shape overrides --

            virtual double
            volume() const override;

            virtual std::string
            to_string() const override;

            inline const polygon& poly() const;
            inline double height() const;

        protected:
            pyramid(const polygon& polygon, double height);

        private:
            polygon mPolygon;
            double mHeight;
    };



};  //-- namespace shapes --

#endif // _SHAPES_PYRAMID_H_
