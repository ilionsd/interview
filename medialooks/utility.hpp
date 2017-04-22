/*
 * utility.hpp
 *
 *  Created on: Apr 22, 2017
 *      Author: ilion
 */

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <cstddef>
#include <sstream>
#include <iostream>

namespace utility {

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

};	//-- namespace utility --



#endif /* UTILITY_HPP_ */
