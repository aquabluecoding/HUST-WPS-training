#include "kmatrix.h"

//初始化函数
template <typename T>
void KMatrix<T>::init(int row, int column)
{
	m_rows = row;
	m_columns = column;
	for (int i = 0; i <= row + 1; i++)
	{
		m_rowIndex.push_back(0);
	}
}

//默认构造函数
template <typename T>
KMatrix<T>::KMatrix()
{
	if (typeid(T) != typeid(char) && typeid(T) != typeid(unsigned char) && typeid(T) != typeid(int) && typeid(T) != typeid(unsigned int) && typeid(T) != typeid(short) && typeid(T) != typeid(unsigned short) && typeid(T) != typeid(long) && typeid(T) != typeid(unsigned long) && typeid(T) != typeid(long long) && typeid(T) != typeid(unsigned long long) && typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(T) != typeid(long double))
		assert(false);
}

//行列构造函数
template <typename T>
KMatrix<T>::KMatrix(int row, int column)
{
	if (typeid(T) != typeid(char) && typeid(T) != typeid(unsigned char) && typeid(T) != typeid(int) && typeid(T) != typeid(unsigned int) && typeid(T) != typeid(short) && typeid(T) != typeid(unsigned short) && typeid(T) != typeid(long) && typeid(T) != typeid(unsigned long) && typeid(T) != typeid(long long) && typeid(T) != typeid(unsigned long long) && typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(T) != typeid(long double))
		assert(false);
	init(row, column);
}

//拷贝构造函数，深拷贝
template <typename T>
KMatrix<T>::KMatrix(const KMatrix<T>& matrix)
{
	if (typeid(T) != typeid(char) && typeid(T) != typeid(unsigned char) && typeid(T) != typeid(int) && typeid(T) != typeid(unsigned int) && typeid(T) != typeid(short) && typeid(T) != typeid(unsigned short) && typeid(T) != typeid(long) && typeid(T) != typeid(unsigned long) && typeid(T) != typeid(long long) && typeid(T) != typeid(unsigned long long) && typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(T) != typeid(long double))
		assert(false);
	init(matrix.getRows(), matrix.getCols());
	for (auto it = matrix.begin(); it != matrix.end(); it++) 
	{
		setData(get<0>(*it), get<1>(*it), get<2>(*it));
	}
}

//获得行数
template <typename T>
int  KMatrix<T>::getRows() const
{
	return m_rows;
}

//获得列数
template <typename T>
int  KMatrix<T>::getCols() const
{
	return m_columns;
}

//设置值
template <typename T>
void   KMatrix<T>::setData(int row, int col, T value)
{
	if (row < 1 || row > m_rows || col < 1 || col > m_columns) 
		return;
	int temp = m_rowIndex[row];
	for (; temp < m_rowIndex[row + 1]; temp++) 
	{
		if (get<0>(m_matrix[temp]) == row && get<1>(m_matrix[temp]) == col)
		{
			get<2>(m_matrix[temp]) = value;
			return;
		}
		if (get<1>(m_matrix[temp]) > col) 
			break;
	}
	tuple<int, int, T> t(row, col, value);
	m_matrix.insert(m_matrix.begin() + temp, t);
	for (int i = row + 1; i <= m_rows + 1; i++) 
		m_rowIndex[i]++;
}

//获取值
template <typename T>
T KMatrix<T>::getData(int row, int col)
{
	if (row < 1 || row > m_rows || col < 1 || col > m_columns)
	{
		cout << "查找越界！" << endl;
		return 0;
	}
	int temp = m_rowIndex[row];
	for (; temp < m_rowIndex[row + 1]; temp++) 
	{
		if (get<0>(m_matrix[temp]) == row && get<1>(m_matrix[temp]) == col)
			return get<2>(m_matrix[temp]);	
		if (get<1>(m_matrix[temp]) > col)
			break;
	}
	return 0;
}

//删除行
template <typename T>
void KMatrix<T>::eraseRow(int row)
{
	if (row < 1 || row > m_rows) 
		return;
	auto it = m_matrix.begin() + m_rowIndex[row];
	if (row == m_rows)
	{
		while (it != m_matrix.end())
		{
			it = m_matrix.erase(it);
		}
	}
	else
	{
		for (int i = 0; i < m_rowIndex[row] - m_rowIndex[row - 1]; i++)
		{
			it = m_matrix.erase(it);
		}
		int div = m_rowIndex[row];
		while (it != m_matrix.end())
		{
			tuple<int, int, T> temp(get<0>(*it) - 1, get<1>(*it), get<2>(*it));
			m_matrix[div] = temp;
			it++;
			div++;
		}
	}
	for (int i = row + 1; i < m_rows; i++)
	{
		m_rowIndex[i] = m_rowIndex[i + 1] - m_rowIndex[i] + m_rowIndex[i - 1];
	}
	m_rowIndex.pop_back();
	m_rows--;
}

//删除列
template <typename T>
void KMatrix<T>::eraseCol(int col)
{
	if (col < 1 || col > m_columns) 
		return;
	for (auto it = m_matrix.begin(); it != m_matrix.end(); )
	{
		if (get<1>(*it) == col)
			it = m_matrix.erase(it);
		else
			it++;
	}
	for (int i = 0, rowNum = 1; i < m_matrix.size(); i++)
	{
		if (i >= m_rowIndex[rowNum+1])
			rowNum++;
		if (get<1>(m_matrix[i]) > col)
		{
			tuple<int, int, T> temp(get<0>(m_matrix[i]), get<1>(m_matrix[i]) - 1, get<2>(m_matrix[i]));
			m_matrix[i] = temp;
			for (int i = rowNum + 1; i <= m_rows; i++)
				m_rowIndex[rowNum + 1]--;
			m_rowIndex.pop_back();
		}
	}
	m_columns--;
}

//开始迭代器
template <typename T>
auto KMatrix<T>::begin() const
{
	return m_matrix.begin();
}

//结束迭代器
template <typename T>
auto KMatrix<T>::end() const
{
	return m_matrix.end();
}

//加
template <typename T>
KMatrix<T> KMatrix<T>::operator+(const KMatrix<T>& b)
{
	if (m_rows != b.getRows() || m_columns != b.getCols()) 
	{
		cout << "不符合相加条件！" << endl;
		return KMatrix<T>(0, 0);
	}
	auto it1 = m_matrix.begin();
	auto it2 = b.begin();
	KMatrix<T> ans(m_rows, m_columns);
	while (it1 != m_matrix.end() || it2 != b.end()) 
	{
		if (it1 == m_matrix.end())
		{
			ans.setData(get<0>(*it2), get<1>(*it2), get<2>(*it2));
			it2++;
		}
		else if (it2 == b.end())
		{
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1));
			it1++;
		}
		else if ((get<0>(*it1) == get<0>(*it2)) && (get<1>(*it1) == get<1>(*it2))) 
		{ 
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1) + get<2>(*it2));
			it1++;
			it2++;
		}
		else if ((get<0>(*it1) > get<0>(*it2)) || ((get<1>(*it1) > get<1>(*it2)) && (get<0>(*it1) == get<0>(*it2)))) 
		{ 
			ans.setData(get<0>(*it2), get<1>(*it2), get<2>(*it2));
			it2++;
		}
		else if ((get<0>(*it1) < get<0>(*it2)) || ((get<1>(*it1) < get<1>(*it2)) && (get<0>(*it1) == get<0>(*it2)))) 
		{ 
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1));
			it1++;
		}
	}
	return ans;
}

//减
template <typename T>
KMatrix<T> KMatrix<T>::operator-(const KMatrix<T>& b)
{
	if (m_rows != b.getRows() || m_columns != b.getCols()) 
	{
		cout << "不符合相减条件" << endl;
		return KMatrix<T>(0, 0);
	}
	auto it1 = m_matrix.begin();
	auto it2 = b.begin();
	KMatrix<T> ans(m_rows, m_columns);
	while (it1 != m_matrix.end() || it2 != b.end()) 
	{
		if (it1 == m_matrix.end()) 
		{
			ans.setData(get<0>(*it2), get<1>(*it2), -get<2>(*it2));
			it2++;
		}
		else if (it2 == b.end()) 
		{
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1));
			it1++;
		}
		else if ((get<0>(*it1) == get<0>(*it2)) && (get<1>(*it1) == get<1>(*it2))) 
		{
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1) - get<2>(*it2));
			it1++;
			it2++;
		}
		else if ((get<0>(*it1) > get<0>(*it2)) || ((get<1>(*it1) > get<1>(*it2)) && (get<0>(*it1) == get<0>(*it2)))) 
		{
			ans.setData(get<0>(*it2), get<1>(*it2), -get<2>(*it2));
			it2++;
		}
		else if ((get<0>(*it1) < get<0>(*it2)) || ((get<1>(*it1) < get<1>(*it2)) && (get<0>(*it1) == get<0>(*it2)))) 
		{
			ans.setData(get<0>(*it1), get<1>(*it1), get<2>(*it1));
			it1++;
		}
		
	}
	return ans;
}

//叉乘
template <typename T>
KMatrix<T> KMatrix<T>::operator*(const KMatrix<T>& b)
{
	if (m_columns != b.getRows()) 
	{
		cout << "不符合相乘条件" << endl;
		return KMatrix<T>(0, 0);
	}
	
	KMatrix<T> ans(m_rows, b.getCols());
	
	KMatrix<T> bT = b.transpose();			//转置被乘的矩阵b，方便乘法的遍历
	auto it1 = m_matrix.begin();
	for (int i = 1; i <= m_rows; i++) 
	{
		auto it2 = bT.begin();
		for (int j = 1; j <= b.getCols(); j++) 
		{
			T sum = 0;
			it1 = m_matrix.begin() + m_rowIndex[i];

			for (int k = m_rowIndex[i]; k < m_rowIndex[i + 1] && it2 != bT.end();) 
			{ 
				if (get<0>(*it2) > j || get<0>(*it1) != i) 
					break;
				if (get<1>(*it1) == get<1>(*it2) && get<0>(*it2) == j) 
				{ 
					sum += get<2>(*it1) * get<2>(*it2);
					it1++;
					it2++;
					k++;
				}
				else if (get<1>(*it1) < get<1>(*it2) && get<0>(*it2) == j) 
				{ 
					it1++;
					k++;
				}
				else 
				{ 
					it2++;
				}
			}
			if (sum != 0) 
				ans.setData(i, j, sum);
		}
	}
	return ans;
}

//转置
template <typename T>
KMatrix<T> KMatrix<T>::transpose() const
{
	KMatrix<T> ans(m_columns, m_rows);
	for (auto it = m_matrix.begin(); it != m_matrix.end(); it++) 
	{
		ans.setData(get<1>(*it), get<0>(*it), get<2>(*it)); 
	}
	return ans;
}

//输出
template <typename T>
void KMatrix<T>::print() const
{
	auto it = m_matrix.begin();
	for (int i = 1; i <= m_rows; i++) 
	{
		for (int j = 1; j <= m_columns; j++) 
		{
			if ((it != m_matrix.end()) && (get<0>(*it) == i && get<1>(*it) == j))
				cout << get<2>(*it++) << '\t';
			else
				cout << "0\t";
		}
		cout << endl;
	}
}