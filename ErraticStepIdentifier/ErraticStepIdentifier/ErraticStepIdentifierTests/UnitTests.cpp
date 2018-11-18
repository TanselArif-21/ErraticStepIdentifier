#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "CppUnitTest.h"
#include "../ErraticStepIdentifier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

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

		TEST_METHOD(TestMethod10)
		{
			//Use the first 5 entries of the test file to return the erraticity to 3 d.p.

			vector <float*> lines;

			string fileName = "C:\\Users\\HVAD\\Documents\\MyStuff\\TempErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifierTests\\TestFiles\\2017-01-20Z14-30-05.steplog";

			lines = ErraticStepIdentifier::GetCoordsFromFile(fileName, ',');

			vector <float*> lines2;

			for (int i = 0; i < 5; i++)
			{
				lines2.push_back(lines[i]);
			}

			float result = ErraticStepIdentifier::Erraticity(lines2);

			Assert::AreEqual(ErraticStepIdentifier::roundFloat(0.36278710f,3), ErraticStepIdentifier::roundFloat(result,3));
		}

		TEST_METHOD(TestMethod11)
		{
			//Use the next 4 entries of the test file to return the erraticity to 3 d.p.

			vector <float*> lines;

			string fileName = "C:\\Users\\HVAD\\Documents\\MyStuff\\TempErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifierTests\\TestFiles\\2017-01-20Z14-30-05.steplog";

			lines = ErraticStepIdentifier::GetCoordsFromFile(fileName, ',');

			vector <float*> lines2;

			for (int i = 1; i < 5; i++)
			{
				lines2.push_back(lines[i]);
			}

			float result = ErraticStepIdentifier::Erraticity(lines2);

			Assert::AreEqual(ErraticStepIdentifier::roundFloat(0.447f, 3), ErraticStepIdentifier::roundFloat(result, 3));
		}

		TEST_METHOD(TestMethod12)
		{
			//Use the next first 4 entries of the test file to return the erraticity to 3 d.p. The sensitivity is set to 0.

			vector <float*> lines;

			string fileName = "C:\\Users\\HVAD\\Documents\\MyStuff\\TempErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifierTests\\TestFiles\\2017-01-20Z14-30-05.steplog";

			lines = ErraticStepIdentifier::GetCoordsFromFile(fileName, ',');

			vector <float*> lines2;

			for (int i = 1; i < 5; i++)
			{
				lines2.push_back(lines[i]);
			}

			float result = ErraticStepIdentifier::Erraticity(lines2,0);

			Assert::AreEqual(ErraticStepIdentifier::roundFloat(0.0f, 3), ErraticStepIdentifier::roundFloat(result, 3));
		}

		TEST_METHOD(TestMethod13)
		{
			//Full erraticity test

			vector <float*> lines;

			vector <string*> lines2;

			vector <float*> lines3;

			string fileName = "C:\\Users\\HVAD\\Documents\\MyStuff\\TempErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifierTests\\TestFiles\\2017-01-20Z14-30-05.steplog";
			string fileName2 = "C:\\Users\\HVAD\\Documents\\MyStuff\\TempErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifier\\ErraticStepIdentifierTests\\TestFiles\\TestFile1.txt";


			lines = ErraticStepIdentifier::GetCoordsFromFile(fileName, ',');
			lines2 = ErraticStepIdentifier::GetTimeStampsFromFile(fileName, ',');

			float* f = ErraticStepIdentifier::GetErraticitiesArray(lines, 0, 5);

			string line;

			ifstream myfile(fileName2);
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					float* arr;

					arr = ErraticStepIdentifier::splitByDelimiter(line, ',');

					lines3.push_back(arr);
				}
				myfile.close();
			}
			else
			{
				cout << "Unable to open file\n";
			}

			for (int i = 0; i < lines3.size(); i++)
			{
				Assert::AreEqual(ErraticStepIdentifier::roundFloat(lines3[i][1],3), ErraticStepIdentifier::roundFloat(f[i],3));
			}
		}

	};
}