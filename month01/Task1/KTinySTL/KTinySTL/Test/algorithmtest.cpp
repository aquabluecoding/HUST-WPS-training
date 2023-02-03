#include "algorithmtest.h"

namespace TinySTL
{
	namespace AlgorithmTest
	{
		void testFind()
		{
			std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			assert(TinySTL::find(v.begin(), v.end(), 5) != v.end());
			assert(TinySTL::find(v.begin(), v.end(), 10) == v.end());
			assert(TinySTL::find_if(v.begin(), v.end(), [](int i){return i < 0; }) == v.end());
			assert(TinySTL::find_if_not(v.begin(), v.end(), [](int i){return i < 0; }) != v.end());
		}
		
		
		void testSort()
		{
			int arr1[1] = { 0 };
			TinySTL::sort(std::begin(arr1), std::end(arr1));
			assert(std::is_sorted(std::begin(arr1), std::end(arr1)));

			int arr2[2] = { 1, 0 };
			TinySTL::sort(std::begin(arr2), std::end(arr2));
			assert(std::is_sorted(std::begin(arr2), std::end(arr2)));

			int arr3[3] = { 2, 1, 3 };
			TinySTL::sort(std::begin(arr3), std::end(arr3));
			assert(std::is_sorted(std::begin(arr3), std::end(arr3)));

			int arr4[100];
			std::random_device rd;
			for (auto i = 0; i != 10; ++i)
			{
				for (auto& n : arr4)
				{
					n = rd() % 65536;
				}
				TinySTL::sort(std::begin(arr4), std::end(arr4));
				assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
			}
		}
		

		void testAllCases()
		{
			testFind();
			testSort();
		}
	}
}