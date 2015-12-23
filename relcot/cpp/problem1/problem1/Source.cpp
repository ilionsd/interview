/*

	Semyon Burov, 2015
*/

#include <iostream>
#include <functional>
#include <array>
#include <algorithm> 


struct solution {
	double V;
	double C;

	double quantity() {
		return V * C;
	};

	solution() :
		V(0),
		C(0)
	{};

	solution(double volume, double concentration) :
		V(volume),
		C(concentration)
	{};


};


int main() {

	using std::cin;
	using std::cout;
	using std::endl;

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	solution
		barrelRez,
		barrelZ(2, 0.02),
		barrelY(2, 0.1),
		barrelX(2, 0.5);

	cin >> barrelRez.V >> barrelRez.C;

/*
	Consider this problem as system of linear equations :
		x + y + z = V;
		cx*x + cy*y + cz*z = cv*V,
	where
		x - Volume of 50 % solution;
		y - Volume of 10 % solution;
		z - Volume of  2 % solution;

		c_ - concentration of corresponding solution.

	Consider `z` - independent variable, obtain:
		z = z;
		y = -(cv*V - cx*V) / (cx - cy) - [(cx - cz) / (cx - cy)] * z;
		x = (cv*V - cy*V) / (cx - cy) + [(cy - cz) / (cx - cy)] * z,
	where
		cv, V - input data;
		cx, cy, cz - conditions of problem.

	So,
		z = z;
		y = ky*z + fy(cv, V);
		x = kx*z + fx(cv, V),
	where
		ky = -(cx - cz) / (cx - cy);
		kx = (cy - cz) / (cx - cy);
		fy(cv, V) = -(cv*V - cx*V) / (cx - cy);
		fx(cv, V) = (cv*V - cy*V) / (cx - cy).

	Finally, to select `z` properly, we will use inequations of volume :
		0 <= x <= Vx;
		0 <= y <= Vy;
		0 <= z <= Vz,
	that transforms into:
		0 <= kx*z + fx(cv, V) <= Vx;
		0 <= ky*z + fy(cv, V) <= Vy;
		0 <= z <= Vz,
	or:
		-fx(cv, V) <= kx*z <= Vx - fx(cv, V);
		-fy(cv, V) <= ky*z <= Vy - fy(cv, V);
		0 <= z <= Vz.

	We can consider this as criteria of selection of z and futher obtain y(z, cv, V) and x(z, cv, V).

	The final form will be obtained after division inequations by `k_`.
	This can invert signs in inequation, so I wouldn't write it here.
*/

	double cx_minus_cy = barrelX.C - barrelY.C;
	double 
		kx =   (barrelY.C - barrelZ.C) / cx_minus_cy,
		ky = - (barrelX.C - barrelZ.C) / cx_minus_cy;

	std::function<double(solution)> 
		fx = [cx_minus_cy, barrelY] (solution barrelRez) -> double {
		return   (barrelRez.C - barrelY.C) * barrelRez.V / cx_minus_cy;
	},
		fy = [cx_minus_cy, barrelX] (solution barrelRez) -> double {
		return - (barrelRez.C - barrelX.C) * barrelRez.V / cx_minus_cy;
	};

	auto inequationBoundExpress = [] (solution barrel, double k, std::function<double(solution)> f, bool hasAdditional) -> std::function<double(solution)> {
		std::function<double(solution)> bound;
		if (hasAdditional) bound = [barrel, k, f] (solution barrelRez) -> double {
			return (barrel.V - f(barrelRez)) / k;
		};
		else bound = [k, f](solution barrelRez) -> double {
			return -f(barrelRez) / k;
		};
		return bound;
	};

	std::function<double(solution)>
		inequationLeftBoundFromX  = inequationBoundExpress(barrelX, kx, fx, kx < 0),
		inequationRightBoundFromX = inequationBoundExpress(barrelX, kx, fx, kx > 0),
		inequationLeftBoundFromY  = inequationBoundExpress(barrelY, ky, fy, ky < 0),
		inequationRightBoundFromY = inequationBoundExpress(barrelY, ky, fy, ky > 0);

	std::function<double(solution)> inequationLeftBoundFromZ = [](solution barrel) -> double {
		return 0;
	};
	std::function<double(solution)> inequationRightBoundFromZ = [barrelZ](solution barrel) -> double {
		return barrelZ.V;
	};

	std::array<double, 3> inequationLeftBounds = {
		inequationLeftBoundFromX(barrelRez),
		inequationLeftBoundFromY(barrelRez),
		inequationLeftBoundFromZ(barrelRez)
	};
	std::array<double, 3> inequationRightBounds = {
		inequationRightBoundFromX(barrelRez),
		inequationRightBoundFromY(barrelRez),
		inequationRightBoundFromZ(barrelRez)
	};

	auto maxElementIterator = std::max_element(inequationLeftBounds.begin(), inequationLeftBounds.end());
	double leftBoundZ = *maxElementIterator;

	auto minElementIterator = std::min_element(inequationRightBounds.begin(), inequationRightBounds.end());
	double rightBoundZ = *minElementIterator;


	if (leftBoundZ > rightBoundZ) {
		//-- There is no `z` for such `cv` and `V` --
		cout << "There is no solution";
	}
	else {
		/* 
			We can pick any `z` from [leftBoundZ; rightBoundZ] 
			selection of `z` can optimize consumption of solutions in barrels by some criteria.
			Now lets pick `z` = `leftBoundZ` to minimize consumption of 2% solution in barrel z.
		*/
		double z = leftBoundZ;
		double y = ky * z + fy(barrelRez);
		double x = kx * z + fx(barrelRez);

		cout << "Use" << endl;
		cout << x << " of 50% solution" << endl;
		cout << y << " of 10% solution" << endl;
		cout << z << " of 2% solution";
	}
	
	return 0;
}
