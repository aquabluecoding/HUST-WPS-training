#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include "test_util.h"

#include "../algorithm.h"
#include <algorithm>

#include <array>
#include <cctype>
#include <cstring>
#include <cassert>
#include <functional>
#include <list>
#include <random>
#include <vector>

#include "../klist.h"
#include "../kvector.h"


namespace TinySTL
{
	namespace AlgorithmTest
	{
		void testFind();
		void testSort();
		void testAllCases();
	}
}

#endif