#ifndef __K_MATRIX_H__
#define __K_MATRIX_H__

#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include "vld.h"
using namespace std;

template <typename T>
class KMatrix
{
public:
	KMatrix();													//默认构造函数
	KMatrix(int row = 0, int column = 0);						//带参数构造函数
	KMatrix(const KMatrix<T>& matrix);							//复制构造函数
	void init(int row, int column);								//初始化行列信息
	int getRows() const;										//获得行数
	int getCols() const;										//获得列数
	void setData(int row, int col, T value);					//设置值
	T getData(int row, int col);								//得到值
	void eraseRow(int row);										//删除行
	void eraseCol(int col);										//删除列

	auto begin() const;											//开始迭代器
	auto end() const;											//结束迭代器

	KMatrix<T> operator+(const KMatrix<T>& b);					//加
	KMatrix<T> operator-(const KMatrix<T>& b);					//减
	KMatrix<T> operator*(const KMatrix<T>& b);					//乘
	KMatrix<T> transpose() const;								//转置
	void print() const;											//打印输出

private:
	int m_rows;													//行数								
	int m_columns;												//列数
	vector <tuple<int, int, T>> m_matrix;						//三元组（行号，列号，值）
	vector <int> m_rowIndex;									//记录矩阵中每行第一个非0元素在m_matrix中的位置
};

#endif 
