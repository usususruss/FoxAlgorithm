#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const string QUESTION = "Would you like to enter matrixs\' data manually? [Y/N]";

int dimension;
double **A, **B, **C;

template<typename T>
T getValue(T &value, string title) {
	while (1) {
		cout << title;
		cin >> value;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else { break; }
	}
	return value;
}

void allocateMatrix(double **M, int dimension) { // for M[n][n] matrixes
	M = new double*[dimension];
	for (int i = 0; i < dimension; i++) {
		M[i] = new double[dimension];
	}
}

string toLowerCase(string &str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

bool confirm(string question) {
	question += "Answer: ";
	string answer;
	do {
		answer = getValue(answer, question);
		toLowerCase(answer);
	} while (answer != "y" && answer != "n");

	return answer == "y";
}

void fillManually(double **M, int dimension) {
	allocateMatrix(M, dimension);
	// todo manual fill
}

void fillAutomatic(double **M, int dimension) {
	allocateMatrix(M, dimension);
	for (int i = 0; i < dimension * dimension; i++) {
		M[i / dimension][i % dimension] = (i / dimension) * (i % dimension);
	}
}

int main()
{
	do {
		dimension = getValue(dimension, "dimension = ");
	} while (dimension < 2 || dimension > 1100);

	if (dimension < 5 && confirm(QUESTION)) {
		fillManually(A, dimension);
		fillManually(B, dimension);
	}
	else {
		fillAutomatic(A, dimension);
		fillAutomatic(B, dimension);
	}

	// todo algorithm

	return 0;
}