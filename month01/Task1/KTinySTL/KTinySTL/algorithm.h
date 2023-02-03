#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstring>
#include <utility>

#include "allocator.h"
#include "functional.h"
#include "iterator.h"
#include "type_traits.h"
#include "utility.h"

namespace TinySTL
{
	//********* [fill] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}
	//*********** [min] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T>
	const T& min(const T& a, const T& b) { return !(b < a) ? a : b; }
	template <class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp) { return !comp(b, a) ? a : b; }
	//*********** [max] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T>
	const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp) { return (copm(a, b)) ? b : a; }
	
	//********** [find] *************************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; ++first)
			if (*first == val)
				break;
		return first;
	}
	//********** [find_if] *************************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class InputIterator, class UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
				break;
		}
		return first;
	}
	//********** [find_if_not] *************************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class InputIterator, class UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		for (; first != last; ++first)
		{
			if (!pred(*first))
				break;
		}
		return first;
	}
	
	
	//********** [sort] ******************************
	//********* [Algorithm Complexity: O(NlogN)] ****************
	namespace 
	{
		template<class RandomIterator, class BinaryPredicate>
		typename iterator_traits<RandomIterator>::value_type
			mid3(RandomIterator first, RandomIterator last, BinaryPredicate pred)
		{//[first, last]
			auto mid = first + (last + 1 - first) / 2;
			if (pred(*mid, *first))
				swap(*mid, *first);
			if (pred(*last, *mid))
				swap(*last, *mid);
			if (pred(*last, *first))
				swap(*last, *first);
			auto ret = *mid;
			swap(*mid, *(last - 1));//将mid item换位作为哨兵
			return ret;
		}
		template<class RandomIterator, class BinaryPredicate>
		void bubble_sort(RandomIterator first, RandomIterator last, BinaryPredicate pred)
		{
			auto len = last - first;
			for (auto i = len; i != 0; --i)
			{
				bool swaped = false;
				for (auto p = first; p != (first + i - 1); ++p)
				{
					if (pred(*(p + 1), *p))
					{
						swap(*(p + 1), *p);
						swaped = true;
					}
				}
				if (!swaped)
					break;
			}
		}
	}
	template<class RandomIterator>
	void sort(RandomIterator first, RandomIterator last)
	{
		return sort(first, last, less<typename iterator_traits<RandomIterator>::value_type>());
	}
	template<class RandomIterator, class BinaryPredicate>
	void sort(RandomIterator first, RandomIterator last, BinaryPredicate pred)
	{
		if (first >= last || first + 1 == last)
			return;
		if (last - first <= 20)//区间长度小于等于20的采用冒泡排序更快
			return bubble_sort(first, last, pred);
		auto mid = mid3(first, last - 1, pred);
		auto p1 = first, p2 = last - 2;
		while (p1 < p2)
		{
			while (pred(*p1, mid) && (p1 < p2)) ++p1;
			while (!pred(*p2, mid) && (p1 < p2)) --p2;
			if (p1 < p2)
			{
				swap(*p1, *p2);
			}
		}
		swap(*p1, *(last - 2));//将作为哨兵的mid item换回原来的位置
		sort(first, p1, pred);
		sort(p1 + 1, last, pred);
	}
	
	//********** [distance] ******************************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag){
		typename iterator_traits<InputIterator>::difference_type dist = 0;
		while (first++ != last)
		{
			++dist;
		}
		return dist;
	}
	template<class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag)
	{
		auto dist = last - first;
		return dist;
	}
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last)
	{
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		return _distance(first, last, iterator_category());
	}
	
}


#endif