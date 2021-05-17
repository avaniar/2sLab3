#include "pch.h"
#include "CppUnitTest.h"
#include"..\Lab3\Header.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace flights;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(correct_entry)
		{
			ifstream file("C:\\Users\\avani\\source\\repos\\AISD\\Lab3\\Lab3\\texttest.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			string* cities = new string[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			matrixentry(file, Matrix, size, cities);
			string citiestest[3] = { "St. Petersburg", "Moscow", "Samara" };
			int Matrixtest[3][3] = { {0,10,100000},{20,0,15},{100000,20,0} };
			for (int i = 0; i < size; i++)
			{
				Assert::IsTrue(cities[i] == citiestest[i]);
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
				}
			}
		}
		TEST_METHOD(correct_findacity)
		{
			string citiestest[3] = { "St. Petersburg", "Moscow", "Samara" };
			string city = "Moscow";
			int sizecities = 3;
			Assert::AreEqual(findacity(city, citiestest, sizecities), 1);
		}
		TEST_METHOD(correct_algorithm)
		{
			ifstream file("C:\\Users\\avani\\source\\repos\\AISD\\Lab3\\Lab3\\texttest.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			string* cities = new string[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			int** Ways = new int* [size];
			for (int i = 0; i < size; i++)
				Ways[i] = new int[size];
			matrixentry(file, Matrix, size, cities);
			algorithm(Matrix, size, Ways);
			int Matrixtest[3][3] = { {0,10,25},{20,0,15},{40,20,0} };
			int waystest[3][3] = { {0,2,2},{1,0,3},{2,2,0} };
			for(int i=0;i<size;i++)
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
					Assert::AreEqual(Ways[i][j], waystest[i][j]);
				}
		}
	};
}
