#ifndef _SHAPE_CUBE_H_
#define _SHAPE_CUBE_H_

#include <memory>
#include <sstream>

#include "shape.hpp"
#include "../include/cloning.hpp"

namespace shapes {

    std::unique_ptr<shape>
    make_cube(double side);

	std::unique_ptr<shape>
	make_cube(const std::vector<double> &agrs);

    class cube :
        public shape,
        public cloning::cloner<cube, shape>
    {
        public:

            friend std::unique_ptr<shape>
            make_cube(double);

            cube(const cube& other);

            virtual ~cube() override {};

            virtual double
            volume() const override;

            virtual std::string
            to_string() const override;

            inline double side() const;


        protected:
            cube(double side);

        private:
            double mSide;
    };

};  //-- namespace shapes --

#endif // _SHAPE_CUBE_H_
