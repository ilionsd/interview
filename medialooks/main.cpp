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
#include <memory>
#include <string>
#include <sstream>


#include "utility.hpp"


using std::size_t;
using std::ptrdiff_t;

using std::cout;
using std::endl;


template<typename T1, typename T2>
std::string to_string(const std::pair<T1, T2> &p) {
	std::stringstream ss;
	ss << "{" << p.first << ", " << p.second << "}";
	return ss.str();
}

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& stream, const std::pair<T1, T2> &p) {
	stream << to_string(p);
	return stream;
}


inline
std::pair<ptrdiff_t, ptrdiff_t>
operator+ (const std::pair<ptrdiff_t, ptrdiff_t> &x, const std::pair<ptrdiff_t, ptrdiff_t> &y) {
	return {x.first + y.first, x.second + y.second};
}

template<typename T1, typename T2>
inline
std::pair<T1, T2>&
operator+= (std::pair<T1, T2> &x, const std::pair<T1, T2> &y) {
	std::get<0>(x) = std::get<0>(x) + std::get<0>(y);
	std::get<1>(x) = std::get<1>(x) + std::get<1>(y);
	return x;
}

template<typename T1, typename T2, typename T3>
inline
std::pair<T1, T2>
operator* (const std::pair<T1, T2> &x, const T3 k) {
	return {x.first * k, x.second * k};
}

template<typename T1, typename T2, typename T3>
inline
std::pair<T1, T2>&
operator*= (std::pair<T1, T2> &p, const T3 k) {
	p.first *= k;
	p.second *= k;
	return p;
}

template<typename T1, typename T2, typename T3>
inline std::pair<T1, T2>
operator% (const std::pair<T1, T2>& p, const T3 modulo) {
	return {p.first % modulo, p.second % modulo};
}

template<typename T1, typename T2, typename T3>
inline std::pair<T1, T2>&
operator%= (std::pair<T1, T2>& p, const T3 modulo) {
	p.first %= modulo;
	p.second %= modulo;
	return p;
}


struct shift {
	using type = std::array<std::pair<ptrdiff_t, ptrdiff_t>, 4>;
	static constexpr type cw	{{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }};
	static constexpr type ccw	{{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} }};
};
constexpr shift::type shift::cw;
constexpr shift::type shift::ccw;

template<typename PFOnElement>
void SnailOrder(size_t nSideSize, bool bFromCenter, const shift::type& shifts, const PFOnElement &pfOnElement) {
	ptrdiff_t k;
	ptrdiff_t loopDirection;
	std::pair<ptrdiff_t, ptrdiff_t> currentIndex, nextIndex;

	if (bFromCenter) {
		k = nSideSize / 2 - 1;
		loopDirection = -1;
	}
	else {
		k = 0;
		loopDirection = 1;
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

std::pair<ptrdiff_t, ptrdiff_t> CalcPos(size_t order, const shift::type& shifts) {
	size_t k = 0, step = 1;
	std::pair<ptrdiff_t, ptrdiff_t> pos {0, 0};
	if (order) {
		while (order > step) {
			order -= step;
			pos += shifts[k++ % shifts.size()] * step;
			step += k % 2 == 0;
		}
		pos += shifts[k++ % 4] * order;
	}
	return pos;
}



enum class corner : char {
	left = 0,
	right = 1,
	bottom = 0,
	top = 2
};

inline corner operator| (const corner a, const corner b) {
	return static_cast<corner>(static_cast<char>(a) | static_cast<char>(b));
}
inline corner operator& (const corner a, const corner b) {
	return static_cast<corner>(static_cast<char>(a) & static_cast<char>(b));
}
template<template <typename> class C, typename T1, typename T2>
inline bool compare(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
	return C<T1>{}(p1.first, p2.first) && C<T2>{}(p1.second, p2.second);
}

template<typename T1, typename T2>
inline std::pair<T2, T1>
swap(const std::pair<T1, T2>& p) {
	return {p.second, p.first};
}




template<typename T>
void FillZigzag(T* _pnMatrixForFill, size_t _nSideSize, const T* _pnSrcElements, corner _nCorner ) {
	std::pair<ptrdiff_t, ptrdiff_t> shift, index, direction;
	bool isRight = static_cast<bool>(_nCorner & corner::right), isTop = static_cast<bool>(_nCorner & corner::top);
	direction.first = (isRight) ? -1 : 1;
	direction.second = (isTop)  ? 1 : -1;
	shift = {-direction.first, direction.second};
	std::pair<ptrdiff_t, ptrdiff_t> zzShift = {direction.first, 0};
	index = { isRight * (_nSideSize - 1), !isTop * (_nSideSize - 1) };

	auto toPlainIndex = [_nSideSize](const std::pair<ptrdiff_t, ptrdiff_t>& idx) {return idx.first * _nSideSize + idx.second;};

	std::pair<ptrdiff_t, ptrdiff_t> topLeftBound = {0, 0}, bottomRightBound = {_nSideSize, _nSideSize};
	for (size_t k = 0; k < _nSideSize * _nSideSize; ++k) {
		_pnMatrixForFill[toPlainIndex(index)] = _pnSrcElements[k];
		auto nextIndex = index + shift;

		if (!compare<std::greater_equal>(nextIndex ,topLeftBound) || !compare<std::less>(nextIndex, bottomRightBound)) {
			if (index % (_nSideSize - 1) == topLeftBound)
				zzShift = swap(zzShift);
			nextIndex = index + zzShift;
			shift *= -1;
			zzShift = swap(zzShift);
		}
		index = nextIndex;
	}
}


template<typename T, size_t N, size_t M>
void desc_element(T (&mat)[N][M], const size_t row, const size_t col, const size_t order) {
	cout << mat[row][col] << " ";
	cout.flush();
}




auto main() -> int {

	namespace u = utility;

	const size_t n = 4;
	unsigned mat[n][n] = { 0 };
	u::fill_ranked(mat);
	u::print(mat);

	auto doSmthg = [&mat](size_t i, size_t j, size_t k)-> void {desc_element(mat, i, j, k);};
	SnailOrder(n, true, shift::ccw, doSmthg);
	cout << endl;
	SnailOrder(n, true, shift::cw, doSmthg);
	cout << endl;
	const size_t orderMax = n * n - 1;
	//CalcPos(3, shift::cw);
	for (size_t order = 0; order <= orderMax; ++order ) {
		cout << CalcPos(order, shift::ccw) << " ";
	}
	cout << endl;

	auto matArray = std::make_unique<unsigned[]>(n * n);
	auto srcArray = std::make_unique<unsigned[]>(n * n);
	u::fill_ranked(srcArray, n * n);
	u::print_as_array(srcArray, n * n);
	for (size_t c = 0; c <= 3; ++c) {
		FillZigzag(matArray.get(), n, srcArray.get(), static_cast<corner>(c));
		u::print_as_mat(matArray, n);
		cout << endl;
	}

	return 0;
}
























