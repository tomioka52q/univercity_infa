#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication3/ConsoleApplication3.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		

		TEST_METHOD(TestMethod10000)
		{
			double result = monte_carlo_rhombus_area(10000);
			Assert::AreEqual(16.0, result, 1.0);
		}

		TEST_METHOD(TestMethod100000)
		{
			double result = monte_carlo_rhombus_area(10000);
			Assert::AreEqual(16.0, result, 0.5);
		}

		TEST_METHOD(TestMethod1000000)
		{
			double result = monte_carlo_rhombus_area(10000);
			Assert::AreEqual(16.0, result, 0.2);
		}
	};
}
