#include "stdafx.h"
#include <iostream>
#include "CppUnitTest.h"
#include "../ErraticStepIdentifier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ErraticStepIdentifierTestProject
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			//Test the most basic case of a straight line trajectory

			float arr[6] = { 5, 4, 3, 2, 3, -5 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::value_crossing_detector(arr, length, 2.5);

			Assert::AreEqual(3, count);
		}

		TEST_METHOD(TestMethod2)
		{
			//Test the case where no crossing has occurred

			float arr[5] = { 5, 4, 3, 2, 3 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(0, count);
		}

		TEST_METHOD(TestMethod3)
		{
			//Test the case where 1 crossing has occurred

			float arr[6] = { 5, 4, 3, 2, 3, -5 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(1, count);
		}

		TEST_METHOD(TestMethod4)
		{
			//Test the case where 3 crossing have occurred

			float arr[8] = { 5, 4, 3, 2, 3, -5, 2, -7 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(3, count);
		}

		TEST_METHOD(TestMethod5)
		{
			//Test the case where 3 crossings have occurred but it lingers on zero(i.e. not crossing)

			float arr[11] = { 5, 4, 3, 2, 3, -5, 2, -7, 0, 0, 0 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(3, count);
		}

		TEST_METHOD(TestMethod6)
		{
			//Test the case where 3 crossings have occurred, it lingers at zero and goes back(i.e.hasn't crossed)

			float arr[13] = { 5, 4, 3, 2, 3, -5, 2, -7, 0, 0, 0, -1, 0 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(3, count);
		}

		TEST_METHOD(TestMethod7)
		{
			//Test the case where 3 crossings occur, it lingers at zero and then crosses

			float arr[16] = { 5, 4, 3, 2, 3, -5, 2, -7, 0, 0, 0, -1, 0, 1, 1, 1 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(4, count);
		}

		TEST_METHOD(TestMethod8)
		{
			//Test the most basic case of a straight line trajectory but starting with a negative

			float arr[11] = { -5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(2, count);
		}

		TEST_METHOD(TestMethod9)
		{
			//Test the most basic case of a straight line trajectory but starting with a zero

			float arr[11] = { 0, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5 };

			int length = sizeof(arr) / sizeof(*arr);

			int count = ErraticStepIdentifier::zero_crossing_detector(arr, length);

			Assert::AreEqual(1, count);
		}

	};
}