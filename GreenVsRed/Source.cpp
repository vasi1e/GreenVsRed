#include <iostream>
#include <string>
#include "Grid.h"
#include "convertOperator.h"

using namespace std;

// Split the input by ", " and returns array
string* splitString(string _string, string* values);

int main() {
	string* values = new string[3];
	char gridSize[100], indexAndNumberofGeneration[100];

	cin.getline(gridSize, 100);
	values = splitString(gridSize, values);

	// The grid takes first height than width because of 2D array 
	Grid grid(convertStringToInt(values[1]), convertStringToInt(values[0]));
	grid.createGenarationZero();

	cin.ignore();
	cin.getline(indexAndNumberofGeneration, 100);
	values = splitString(indexAndNumberofGeneration, values);

	int counter = 0;
	for (int i = 0; i < convertStringToInt(values[2]); i++) {
		grid.makeNextGeneration();

		// Checker for green cell at that index
		if (grid.getAt(convertStringToInt(values[1]), convertStringToInt(values[0])) == 1) {
			counter++;
		}
	}
	cout << counter << endl;
	system("pause");
}

string* splitString(string _string, string* values) {
	string delimiter = ", ";

	size_t pos = 0;
	string token;
	int i = 0;
	while ((pos = _string.find(delimiter)) != string::npos) {
		token = _string.substr(0, pos);
		values[i] = token;
		_string.erase(0, pos + delimiter.length());
		i++;
	}
	values[i] = _string;

	return values;
}