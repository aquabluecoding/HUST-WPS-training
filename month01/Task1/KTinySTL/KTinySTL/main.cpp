#include <iostream>

#include "algorithm.h"
#include "Profiler\profiler.h"

#include "Test\algorithmtest.h"
#include "Test\dequetest.h"
#include "Test\listtest.h"
#include "Test\queuetest.h"
#include "Test\stacktest.h"
#include "Test\vectortest.h"

using namespace TinySTL::Profiler;

int main()
{
	TinySTL::AlgorithmTest::testAllCases();
	TinySTL::DequeTest::testAllCases();
	TinySTL::ListTest::testAllCases();
	TinySTL::QueueTest::testAllCases();
	TinySTL::StackTest::testAllCases();
	TinySTL::VectorTest::testAllCases();
	 
	system("pause");
	return 0;
}