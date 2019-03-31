#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm> // for transform function
#include <cstdlib> // for rand, srand
#include <ctime>
#include <fstream>
#include <regex>
using namespace std;

const string FILL_QUESTION = "Would you like to enter matrixs\' data manually? [Y/N] ";
const string FILE_OUTPUT = "Matrix dimension is too big, output to file? [Y/N] ";
const string PRINT_SKIP = "Output skipped...";
const string FILE_COMPLETE = "Print compelted!";

const string FILE_EXTENSION = ".csv";
const string CSV_DELIMITTER = ";";

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

void allocateMatrix(double **&M, int dimension) { // for M[n][n] matrixes
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



void fillManually(double **&M, int dimension) {
	allocateMatrix(M, dimension);
	
	regex r("/^(((\\+|-)?\d+(\.\d+)?)\ ){0,}(((\\+|-)?\d+(\.\d+)?)\n)/");
	cout << "Enter " << dimension << " rows, " << dimension << " elems in row separated with space:" << endl;

	string row;
	getline(cin, row);

	cout << "row" << row << endl;
	cout << "regexp result = " << regex_match(row, r) << endl;


}

void fillAutomatic(double **&M, int dimension) {
	allocateMatrix(M, dimension);
	srand((unsigned int) time(NULL));
	for (int i = 0; i < dimension * dimension; i++) {
		M[i / dimension][i % dimension] = rand() % 201 - 100;
	}
}

void printToFile(double **&M, string fileName) {
	cout << "Printing to file " << fileName << FILE_EXTENSION << " ..." << endl;
	ofstream file;
	file.open(fileName + FILE_EXTENSION);
	
	for (int i = 0; i < dimension * dimension; i++) {
		string separator = (i % dimension == dimension - 1) ? "\n" : CSV_DELIMITTER;
		file << M[i / dimension][i % dimension] << separator;
	}
	
	file.close();
	cout << FILE_COMPLETE << endl;
}

void printMatrix(double **&M, int dimension, string title) {
	cout << title << endl;
	if (dimension > 10) {
		if (confirm(FILE_OUTPUT)) {
			printToFile(M, title);
		}
		else { cout << PRINT_SKIP << endl; }
	}
	if (dimension < 11) {
		for (int i = 0; i < dimension * dimension; i++) {
			cout << M[i / dimension][i % dimension] << "\t";
			if (i % dimension == dimension - 1) { cout << endl; }
		}
		cout << endl;
	}
}

int main() 
{
	do {
		dimension = getValue(dimension, "dimension = ");
	} while (dimension < 2 || dimension > 1100);

	if (dimension < 5 && confirm(FILL_QUESTION)) {
		fillManually(A, dimension);
		fillManually(B, dimension);
		fillAutomatic(C, dimension); // fill with zeroes
	}
	else {
		fillAutomatic(A, dimension);
		fillAutomatic(B, dimension);
		fillAutomatic(C, dimension);
	}
	printMatrix(A, dimension, "Matrix-A");
	printMatrix(B, dimension, "Matrix-B");


 	//cout << "Size of each matrix = " << (sizeof(double) * dimension * dimension) << " bytes" << endl;




	// todo algorithm
	system("pause");
	return 0;
}