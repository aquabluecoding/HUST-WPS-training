#ifndef _STACK_TEST_H_
#define _STACK_TEST_H_

#include "test_util.h"

#include "../kstack.h"
#include <stack>

#include <cassert>
#include <string>

namespace TinySTL
{
	namespace StackTest
	{
		template<class T>
		using stdSt = std::stack < T > ;
		template<class T>
		using tsSt = TinySTL::KStack < T > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();

		void testAllCases();
	}
}

#endif