/*
 * main.cpp
 *
 *  Created on: Apr 14, 2017
 *      Author: ilion
 */

#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <functional>
#include <string>
#include <sstream>

using std::size_t;
using std::ptrdiff_t;

template<typename T, size_t Rows, size_t Cols>
void fill_ranked(T (&mat)[Rows][Cols]) {
	size_t inc = 0;
	for (size_t row = 0; row < Rows; ++row)
		for (size_t col = 0; col < Cols; ++col)
			mat[row][col] = inc++;
}

template<typename T, size_t Rows, size_t Cols>
void print(T (&mat)[Rows][Cols]) {
	for (size_t row = 0; row < Rows; ++row) {
		for (size_t col = 0; col < Cols; ++col)
			std::cout << mat[row][col] << "	";
		std::cout << std::endl;
	}
}

template<typename T1, typename T2>
std::string to_string(const std::pair<T1, T2> &p) {
	std::stringstream ss;
	ss << "{" << p.first << ", " << p.second << "}";
	return ss.str();
}



//typedef void (*PFOnElement)( int x, int y, int order);

inline
std::pair<ptrdiff_t, ptrdiff_t>
operator+ (const std::pair<ptrdiff_t, ptrdiff_t> &x, const std::pair<ptrdiff_t, ptrdiff_t> &y) {
	return std::make_pair(x.first + y.first, x.second + y.second);
}

inline
std::pair<ptrdiff_t, ptrdiff_t>&
operator+= (std::pair<ptrdiff_t, ptrdiff_t> &x, const std::pair<ptrdiff_t, ptrdiff_t> &y) {
	std::get<0>(x) = std::get<0>(x) + std::get<0>(y);
	std::get<1>(x) = std::get<1>(x) + std::get<1>(y);
	return x;
}

template<typename T>
inline
std::pair<ptrdiff_t, ptrdiff_t>
operator* (std::pair<ptrdiff_t, ptrdiff_t> x, const T k) {
	return std::make_pair(x.first * k, x.second * k);
}

template<typename T>
inline
std::pair<ptrdiff_t, ptrdiff_t>&
operator*= (std::pair<ptrdiff_t, ptrdiff_t> x, const T k) {
	x.first *= k;
	x.second *= k;
	return x;
}



template<typename PFOnElement>
void SnailOrder(size_t nSideSize, bool bFromCenter, const PFOnElement &pfOnElement) {

	std::array<std::pair<ptrdiff_t, ptrdiff_t>, 4> cwShifts		{{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }};
	std::array<std::pair<ptrdiff_t, ptrdiff_t>, 4> ccwShifts	{{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} }};

	const std::array<std::pair<ptrdiff_t, ptrdiff_t>, 4> &shifts = cwShifts;

	ptrdiff_t k;
	ptrdiff_t loopDirection;
	std::pair<ptrdiff_t, ptrdiff_t> currentIndex, nextIndex;

	if (bFromCenter) {
		k = nSideSize / 2 - 1;
		loopDirection = -1;
		nextIndex = {nSideSize / 2 - 1, nSideSize / 2};
	}
	else {
		k = 0;
		loopDirection = 1;
		nextIndex = {0, 0};
	}

	size_t order = 0;
	if (nSideSize % 2 && bFromCenter) {
		size_t temp = nSideSize / 2;
		pfOnElement(temp, temp, order++);
	}

	while (k >= 0 && k < static_cast<ptrdiff_t>(nSideSize) / 2) {
		nextIndex = {k, k};
		auto isBounded = [nSideSize, k](const ptrdiff_t &index) ->
				bool { return index >= static_cast<ptrdiff_t>(k) && index < static_cast<ptrdiff_t>(nSideSize - k); };
		auto isBoundedOrNotNeedToCheck = [&isBounded](const ptrdiff_t shift, const ptrdiff_t index) ->
				bool { return !shift || isBounded(index + shift); };

		for (auto shift : shifts) {
			while ( isBoundedOrNotNeedToCheck(shift.first, nextIndex.first) &&
					isBoundedOrNotNeedToCheck(shift.second, nextIndex.second) ) {
				currentIndex = nextIndex;
				nextIndex = currentIndex + shift;
				if (bFromCenter)
					pfOnElement(nextIndex.first, nextIndex.second, order++);
				else
					pfOnElement(currentIndex.first, currentIndex.second, order++);
			}
		}
		k += loopDirection;
	}
	if (nSideSize % 2 && !bFromCenter) {
		size_t temp = nSideSize / 2;
		pfOnElement(temp, temp, order++);
	}

}

std::pair<ptrdiff_t, ptrdiff_t> CalcPos(const size_t order) {
	size_t k = 0, circuitSize;
	std::pair<ptrdiff_t, ptrdiff_t> pos;
	if (!order)
		pos = {0, 0};
	do {
		circuitSize = k * 2 * 4;
	}
	while (order > circuitSize);
	return {};
}

template<typename T, size_t N, size_t M>
void desc_element(T (&mat)[N][M], const size_t row, const size_t col, const size_t order) {
	std::cout << mat[row][col] << " ";
	std::cout.flush();
}


auto main() -> int {
	const size_t n = 5;
	unsigned mat[n][n] = { 0 };
	fill_ranked(mat);
	print(mat);

	auto doSmthg = [&mat](size_t i, size_t j, size_t k)-> void {desc_element(mat, i, j, k);};
	SnailOrder(n, false, doSmthg);
	std::cout << std::endl;
	SnailOrder(n, true, doSmthg);
	std::cout << std::endl;

	return 0;
}
























