/*
 * main.cpp
 *
 *  Created on: Apr 14, 2017
 *      Author: ilion
 */

#include <cstddef>
#include <iostream>
#include <utility>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <sstream>
#include <type_traits>


#include "utility.hpp"


using std::size_t;
using std::ptrdiff_t;

using std::cout;
using std::endl;


template<typename T1, typename T2>
inline std::string
to_string(const std::pair<T1, T2> &p) {
	std::stringstream ss;
	ss << "{" << p.first << ", " << p.second << "}";
	return ss.str();
}
template<typename T1, typename T2>
inline std::ostream&
operator<< (std::ostream& stream, const std::pair<T1, T2> &p) {
	stream << to_string(p);
	return stream;
}

template<typename T1, typename T2>
inline std::pair<T1, T2>
operator+ (const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2) {
	return {p1.first + p2.first, p1.second + p2.second};
}
template<typename T1, typename T2>
inline std::pair<T1, T2>&
operator+= (std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2) {
	p1.first += p2.first; p1.second += p2.second;
	return p1;
}

template<typename T1, typename T2, typename T3>
inline std::enable_if_t<std::is_arithmetic<T3>::value, std::pair<T1, T2>>
operator* (const std::pair<T1, T2> &x, const T3 k) {
	return {x.first * k, x.second * k};
}
template<typename T1, typename T2, typename T3>
inline std::enable_if_t<std::is_arithmetic<T3>::value, std::pair<T1, T2>&>
operator*= (std::pair<T1, T2> &p, const T3 k) {
	p.first *= k; p.second *= k;
	return p;
}

template<typename T1, typename T2>
inline std::pair<T1, T2>
operator* (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
	return {p1.first * p2.first, p1.second * p2.second};
}
template<typename T1, typename T2>
inline std::pair<T1, T2>&
operator*= (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
	p1.first *= p2.first; p1.second *= p2.second;
	return p1;
}

template<typename T1, typename T2, typename T3>
inline std::enable_if_t<std::is_integral<T3>::value, std::pair<T1, T2>>
operator% (const std::pair<T1, T2>& p, const T3 modulo) {
	return {p.first % modulo, p.second % modulo};
}
template<typename T1, typename T2, typename T3>
inline std::enable_if_t<std::is_integral<T3>::value, std::pair<T1, T2>&>
operator%= (std::pair<T1, T2>& p, const T3 modulo) {
	p.first %= modulo; p.second %= modulo;
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
	while (order > step) {
		order -= step;
		pos += shifts[k++ % shifts.size()] * step;
		step += k % 2 == 0;
	}
	pos += shifts[k++ % 4] * order;
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
	direction.first = (isTop)  ? 1 : -1;
	direction.second = (isRight) ? -1 : 1;
	shift = {-direction.first, direction.second};
	std::pair<ptrdiff_t, ptrdiff_t> zzShiftMultiplier = {1, 0};
	index = { !isTop * (_nSideSize - 1), isRight * (_nSideSize - 1) };

	auto toPlainIndex = [_nSideSize](const std::pair<ptrdiff_t, ptrdiff_t>& idx) {return idx.first * _nSideSize + idx.second;};

	std::pair<ptrdiff_t, ptrdiff_t> topLeftBound = {0, 0}, bottomRightBound = {_nSideSize, _nSideSize};
	for (size_t k = 0; k < _nSideSize * _nSideSize; ++k) {
		_pnMatrixForFill[toPlainIndex(index)] = _pnSrcElements[k];
		auto nextIndex = index + shift;

		if (!compare<std::greater_equal>(nextIndex ,topLeftBound) || !compare<std::less>(nextIndex, bottomRightBound)) {
			if (index % (_nSideSize - 1) == topLeftBound)
				zzShiftMultiplier = swap(zzShiftMultiplier);
			nextIndex = index + direction * zzShiftMultiplier;
			shift *= -1;
			zzShiftMultiplier = swap(zzShiftMultiplier);
		}
		index = nextIndex;
	}
}

template<typename T, size_t N>
void array_rotate(T (&mat)[N][N]) {
	size_t y, i, j;
	T z, x = 0;
	//circuits loop
	for (size_t k = 1; k <= N / 2; ++k) {
		//circuit's elements loop
		for (size_t l = k - 1;l <= N - 1 - k; ++l)
		{
			i = l;
			j = k - 1;
			//swap loop
			for (size_t f = 1; f <= 4; ++f) {
				z = mat[i][j];
				mat[i][j] = x;
				x = z;
				y = i;
				i = N - 1 - j;
				j = y;
			}
			mat[i][j] = x;
		}
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

	cout << "Snail Order" << endl;
	auto doSmthg = [&mat](size_t i, size_t j, size_t k)-> void {desc_element(mat, i, j, k);};
	SnailOrder(n, false, shift::ccw, doSmthg);
	cout << endl;
	SnailOrder(n, true, shift::cw, doSmthg);
	cout << endl;
	const size_t orderMax = n * n - 1;
	//CalcPos(3, shift::cw);
	cout << "CalcPos" << endl;
	for (size_t order = 0; order <= orderMax; ++order ) {
		cout << CalcPos(order, shift::ccw) << " ";
	}
	cout << endl;

	auto matArray = std::make_unique<unsigned[]>(n * n);
	auto srcArray = std::make_unique<unsigned[]>(n * n);
	u::fill_ranked(srcArray, n * n);
	cout << "FillZigzag" << endl;
	u::print_as_array(srcArray, n * n);
	for (size_t c = 0; c <= 3; ++c) {
		FillZigzag(matArray.get(), n, srcArray.get(), static_cast<corner>(c));
		u::print_as_mat(matArray, n);
		cout << endl;
	}

	cout << "90 degrees square array rotation (bonus)" << endl;
	for (size_t rotateNumber = 0; rotateNumber < 4; ++rotateNumber) {
		array_rotate(mat);
		u::print(mat);
		cout << endl;
	}

	return 0;
}
























