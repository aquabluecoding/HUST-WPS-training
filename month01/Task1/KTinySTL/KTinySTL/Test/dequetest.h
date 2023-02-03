#ifndef _DEQUE_TEST_H_
#define _DEQUE_TEST_H_

#include "test_util.h"

#include "../kdeque.h"
#include <deque>

#include <cassert>
#include <string>

namespace TinySTL
{
	namespace DequeTest
	{
		template<class T>
		using stdDQ = std::deque < T > ;
		template<class T>
		using tsDQ = TinySTL::KDeque < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();

		void testAllCases();
	}
}

#endif