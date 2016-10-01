#ifndef _SHAPES_CUBOID_H_
#define _SHAPES_CUBOID_H_

#include <memory>
#include <sstream>

#include "shape.h"
#include "cloning.h"

namespace shapes {

    std::unique_ptr<shape>
    make_cuboid(double length, double height, double width);

	std::unique_ptr<shape>
	make_cuboid(const std::vector<double> &args);

    class cuboid :
        public shape,
        public cloning::cloner<cuboid, shape>
    {
        public:
            virtual ~cuboid() override {};
            cuboid(const cuboid& other);

            friend std::unique_ptr<shape>
            make_cuboid(double, double, double);

            virtual double
            volume() const override;

            virtual std::string
            to_string() const override;

            inline double length() const;
            inline double height() const;
            inline double width() const;

        protected:
            cuboid(double length, double height, double width);

        private:
            double mLength;
            double mHeight;
            double mWidth;
    };

};  //-- namespace shapes --

#endif // _SHAPES_CUBOID_H_
