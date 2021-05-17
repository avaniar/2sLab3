#include<iostream>
#include <Windows.h>
#include"Header.h"
using namespace std;
using namespace flights;
int main()
{
	ifstream file("text.txt");
    string line; int size;
    if (!file.is_open()) // If the file cannot be opened.
        cout << "The file cannot be opened!" << endl;
    getline(file, line);
    size = atoi(line.c_str());
    int** Matrix = new int* [size];//Creation of a matrix of weights.
    for (int i = 0; i < size; i++)
        Matrix[i] = new int[size];
    int** Ways = new int* [size];//Creation of a matrix of paths.
    for (int i = 0; i < size; i++)
        Ways[i] = new int[size];
    string* cities = new string[size];//Creating an array of cities
	matrixentry(file,Matrix,size,cities);
	algorithm(Matrix,size,Ways);
    cout << "List of cities:" << endl;
    for (int i = 0; i < size; i++)
        cout << i + 1 << ". " << cities[i] << endl;
    int firsttown;
    cout << "Select departure city: ";
    cin >> firsttown;
    int secondtown;
    cout << "Select the city of arrival: ";
    cin >> secondtown;
    cout << "The cheapest flight" << endl;
	pathrestoration(Ways, firsttown, secondtown, Matrix, cities);
    cout << "Adjacency matrix" << endl;
    matrixoutput(Matrix, size);
	return 0;
}