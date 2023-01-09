#pragma once

#ifndef NULL
#define NULL 0
#endif

enum Direct {
	TOP, BOTTOM, LEFT, RIGHT
};

template<class T>
class Matrix {
private:
	// 存储信息
	T** data;
	// 存储指针
	int left, right, top, bottom;
	// 存储最大值
	int maxW, maxH;

public:

	Matrix(int width=0, int height=0, const T& elem = T());
	Matrix(const Matrix& matrix);
	~Matrix();

	bool modify(int row, int col, const T& elem);

	// 扩展 行和列
	bool extend(Direct direct, const T& elem = T());

	bool isFull();
	bool checkIndex(int row, int col) const;

	//T& value(int row, int col);
	int bound(Direct direct);

	T* operator[](int row);
	Matrix<T>& operator=(const Matrix<T>& matrix);
};

template<class T>
bool Matrix<T>::modify(int row, int col, const T& elem) {
	if (!checkIndex(row, col)) {
		return false;
	}

	data[row][col] = elem;
}

template<class T>
Matrix<T>::Matrix(int width, int height, const T& elem) {
	maxW = maxH = 50;

	top = 0, bottom = height, left = 0, right = width;

	// 分配动态内存
	data = new T * [maxH];
	for (int i = 0; i < maxH; i++) {
		data[i] = new T[maxW];
	}

	// 根据提供的元素初始化
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i][j] = elem;
		}
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix& matrix) {
	maxW = matrix.maxW, maxH = matrix.maxH;

	top = matrix.top, bottom = matrix.bottom;
	left = matrix.left, right = matrix.right;

	// 分配动态内存
	data = new T * [maxH];
	for (int i = 0; i < maxH; i++) {
		data[i] = new T[maxW];
	}
	
	int row, col;
	for (int i = top; i < bottom; i++) {
		for (int j = left; j < right; j++) {
			row = i >= 0 ? i : i + maxW;
			col = j >= 0 ? j : j + maxH;
			data[row][col] = matrix.data[row][col];
		}
	}
}

template<class T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < maxH; i++) {
		delete[] data[i];
	}
	delete[] data;
}

template<class T>
bool Matrix<T>::extend(Direct direct, const T& elem) {
	if (isFull()) {
		return false;
	}
	// Top 00, Bottom 01, Left 10, right 11
	if (direct & 2) {
		int row = direct & 1 ? right++ : left--;

		for (int i = left; i < right; i++) {
			int index = i >= 0 ? i : i + maxW;
			data[row][index] = elem;
		}
	}
	else {
		int col = direct & 1 ? bottom++ : top--;

		for (int i = top; i < bottom; i++) {
			int index = i >= 0 ? i : i + maxH;
			data[index][col] = elem;
		}
	}

	return true;
}

template<class T>
bool Matrix<T>::isFull() {
	bool flag1 = (right - left) >= (maxW - 1);
	bool flag2 = (bottom - top) >= (maxH - 1);
	
	// 只要有一个超出边界 那么都算超出边界
	return flag1 || flag2;
}

template<class T>
bool Matrix<T>::checkIndex(int row, int col) const {
	bool flag1 = top <= row && row < bottom;
	bool flag2 = left <= col && col < right;
	
	return flag1 && flag2;
}

template<class T>
T* Matrix<T>::operator[](int row) {
	if (checkIndex(row, 0))
		return data[row];
	else
		return NULL;
}

//template<class T>
//T& Matrix<T>::value(int row, int col) {
//	return data[row][col];
//}

template<class T>
int Matrix<T>::bound(Direct direct) {
	switch (direct) {
	case TOP:
		return top;
	case BOTTOM:
		return bottom;
	case LEFT:
		return left;
	case RIGHT:
		return right;
	}
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
	if (this == &matrix) {
		return *this;
	}

	maxW = matrix.maxW, maxH = matrix.maxH;

	top = matrix.top, bottom = matrix.bottom;
	left = matrix.left, right = matrix.right;
	
	this->~Matrix();

	// 分配动态内存
	data = new T * [maxH];
	for (int i = 0; i < maxH; i++) {
		data[i] = new T[maxW];
	}

	int row, col;
	for (int i = top; i < bottom; i++) {
		for (int j = left; j < right; j++) {
			row = i >= 0 ? i : i + maxW;
			col = j >= 0 ? j : j + maxH;

			this->data[row][col] = matrix.data[row][col];
		}
	}

	return *this;
}
