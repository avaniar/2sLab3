#pragma once
#include<iostream>
#include< iomanip >
#include <fstream>
#include<string>
const int maximum=100000;
using namespace std;
namespace flights
{
    void matrixoutput(int** Matrix, int size)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (Matrix[i][j] == maximum)
                    cout << setw(4) << "INF";
                else
                    cout << setw(4) << Matrix[i][j];
                if (j == size - 1)
                    cout << endl;
            }
        cout << endl;
    }
    void pathrestoration(int** Ways, int firsttown, int secondtown, int** Matrix, string* cities)
    {
        if (Matrix[firsttown - 1][secondtown - 1] == maximum)
            cout << "No flight available!" << endl;// there is no way between the peaks
        else
        {
            int c = firsttown;
            while (c != secondtown)
            {
                cout << cities[c - 1] << "-->";
                c = Ways[c - 1][secondtown - 1];
            }
            cout << cities[secondtown - 1] << endl;
            cout << "Cost: " << Matrix[firsttown - 1][secondtown - 1] << endl;
        }
    }
    void algorithm(int** Matrix, int size, int** Ways)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if ((Matrix[i][j] != maximum) && (Matrix[i][j] != 0))
                    Ways[i][j] = j + 1;
                else
                    Ways[i][j] = 0;
        for (int k = 0; k < size; k++)
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if ((Matrix[i][k] + Matrix[k][j]) < Matrix[i][j])
                    {
                        Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
                        Ways[i][j] = Ways[i][k];
                    }
    }

    int findacity(string city, string* cities, int sizecities)
    {
        for (int i = 0; i < sizecities; i++)
        {
            if (city == cities[i])
                return i;
        }
        return -1;
    }
    void matrixentry(ifstream& file, int** Matrix, int size, string* cities)
    {
        string line;
        int sizecities = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                    Matrix[i][i] = 0;
                else
                    Matrix[i][j] = maximum;
            }
        while (!file.eof())
        {
            getline(file, line);
            int firstsemicolon = line.find(";");//We define the boundaries of the names of cities.
            int secondsemicolon = line.find(";", firstsemicolon + 1);
            int thirdsemicolon = line.find(";", secondsemicolon + 1);
            string firstcity = line.substr(0, firstsemicolon);//We separate cities and paths.
            string secondcity = line.substr(firstsemicolon + 1, secondsemicolon - firstsemicolon - 1);
            string firstcost = line.substr(secondsemicolon + 1, thirdsemicolon - secondsemicolon - 1);
            string secondcost = line.substr(thirdsemicolon + 1);
            int digitfirstcost;
            int digitsecondcost;
            if (firstcost != "N/A")
                digitfirstcost = atoi(firstcost.c_str());//We convert the length to a number format.
            else
                digitfirstcost = maximum;
            if (secondcost != "N/A")
                digitsecondcost = atoi(secondcost.c_str());
            else
                digitsecondcost = maximum;
            if (findacity(firstcity, cities, sizecities) == -1)//If you have not found a city in the list, then add a new one and expand the matrix.
            {
                cities[sizecities] = firstcity; sizecities++;
            }
            if (findacity(secondcity, cities, sizecities) == -1)
            {
                cities[sizecities] = secondcity; sizecities++;
            }
            Matrix[findacity(firstcity, cities, sizecities)][findacity(secondcity, cities, sizecities)] = digitfirstcost;
            Matrix[findacity(secondcity, cities, sizecities)][findacity(firstcity, cities, sizecities)] = digitsecondcost;
        }
    }
}