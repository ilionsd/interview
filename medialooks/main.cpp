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

using std::size_t;
using std::ptrdiff_t;

using std::cout;
using std::endl;

template<typename T, size_t Rows, size_t Cols>
void fill_ranked(T (&mat)[Rows][Cols]) {
	size_t inc = 0;
	for (size_t row = 0; row < Rows; ++row)
		for (size_t col = 0; col < Cols; ++col)
			mat[row][col] = inc++;
}
template<typename T>
void fill_ranked(std::unique_ptr<T[]>& arr, const size_t size) {
	for (size_t k = 0; k < size; ++k) {
		arr[k] = k;
	}
}

template<typename T, size_t Rows, size_t Cols>
void print(T (&mat)[Rows][Cols]) {
	for (size_t row = 0; row < Rows; ++row) {
		for (size_t col = 0; col < Cols; ++col)
			cout << mat[row][col] << "	";
		cout << endl;
	}
}

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
	return std::make_pair(x.first + y.first, x.second + y.second);
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
	return std::make_pair<T1, T2>(x.first * k, x.second * k);
}

template<typename T1, typename T2, typename T3>
inline
std::pair<T1, T2>&
operator*= (std::pair<T1, T2> &x, const T3 k) {
	x.first *= k;
	x.second *= k;
	return x;
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

template<typename T>
void FillZigzag(T* _pnMatrixForFill, size_t _nSideSize, const T* _pnSrcElements, corner _nCorner ) {
	std::pair<ptrdiff_t, ptrdiff_t> shift, index, direction;
	bool isRight = static_cast<bool>(_nCorner & corner::right), isTop = static_cast<bool>(_nCorner & corner::top);
	direction.first = (isRight) ? -1 : 1;
	direction.second = (isTop)  ? 1 : -1;
	shift = {-direction.first, direction.second};
	std::array<std::pair<ptrdiff_t, ptrdiff_t>, 2> zzShifts = {{ {0, direction.second}, {direction.first, 0} }};
	index = { isRight * (_nSideSize - 1), !isTop * (_nSideSize - 1) };

	auto toPlainIndex = [_nSideSize](const std::pair<ptrdiff_t, ptrdiff_t>& idx) {return idx.first * _nSideSize + idx.second;};

	std::pair<ptrdiff_t, ptrdiff_t> topLeftBound = {0, 0}, bottomRightBound = {_nSideSize, _nSideSize};
	for (size_t k = 0; k < _nSideSize * _nSideSize; ++k) {
		_pnMatrixForFill[toPlainIndex(index)] = _pnSrcElements[k];
		auto nextIndex = index + shift;

		size_t zzShiftIndex = 0;
		bool shiftInverseFlag = false;
		while (!compare<std::greater_equal>(nextIndex ,topLeftBound) || !compare<std::less>(nextIndex, bottomRightBound)) {
			nextIndex = index + zzShifts.at(zzShiftIndex++);
			shiftInverseFlag = true;
		}
		index = nextIndex;
		if (shiftInverseFlag)
			shift *= -1;
	}
}


template<typename T, size_t N, size_t M>
void desc_element(T (&mat)[N][M], const size_t row, const size_t col, const size_t order) {
	cout << mat[row][col] << " ";
	cout.flush();
}

template<typename T>
void print_as_array(const std::unique_ptr<T[]> &arr, const size_t size) {
	for (size_t k = 0; k < size; ++k)
		cout << arr[k] << " ";
	cout << endl;
}

template<typename T>
void print_as_mat(const std::unique_ptr<T[]> &mat, const size_t sideSize) {
	for (size_t row = 0; row < sideSize; ++row) {
		for (size_t col = 0; col < sideSize; ++col)
			cout << mat[row * sideSize + col] << "	";
		cout << endl;
	}
}


auto main() -> int {
	const size_t n = 4;
	unsigned mat[n][n] = { 0 };
	fill_ranked(mat);
	print(mat);

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
	fill_ranked(srcArray, n * n);
	print_as_array(srcArray, n * n);
	FillZigzag(matArray.get(), n, srcArray.get(), corner::left | corner::top);
	print_as_mat(matArray, n);

	return 0;
}
























