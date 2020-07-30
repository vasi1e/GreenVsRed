#include "Grid.h"
#include "convertOperator.h"

Grid::Grid(unsigned short int _height, unsigned short int _width) {
	this->grid = new int*[_height];
	for (unsigned short int i = 0; i < _height; i++) {
		grid[i] = new int[_width];
	}

	this->height = _height;
	this->width = _width;
}

Grid::Grid(const Grid& other) {
	this->grid = new int*[other.getHeight()];
	for (unsigned short int i = 0; i < other.getHeight(); i++) {
		grid[i] = new int[other.getWidth()];
	}

	this->width = other.getWidth();
	this->height = other.getHeight();

	for (unsigned short int i = 0; i < this->height; i++) {
		for (unsigned short int j = 0; j < this->width; j++) {
			this->grid[i][j] = other.getGrid()[i][j];
		}
	}
}

Grid& Grid::operator=(const Grid& other) {
	if (this != &other) {
		for (unsigned short int i = 0; i < this->getHeight(); i++) {
			delete[] grid[i];
		}
		delete[] this->grid;

		this->grid = new int*[other.getHeight()];
		for (int i = 0; i < other.getHeight(); i++) {
			grid[i] = new int[other.getWidth()];
		}

		for (unsigned short int i = 0; i < this->getHeight(); i++) {
			for (unsigned short int j = 0; j < this->getWidth(); j++) {
				this->grid[i][j] = other.getGrid()[i][j];
			}
		}
	}

	return *this;
}

int Grid::getAt(unsigned short int x, unsigned short int y) {
	// Checker for asking for unreachable cell 
	if (x < 0 || y < 0 || x > this->getHeight() - 1 || y > this->getWidth() - 1) {
		return 0;
	}
	else {
		return this->getGrid()[x][y];
	}
}

Grid::~Grid() {
	for (unsigned short int i = 0; i < this->getHeight(); i++) {
		delete[] grid[i];
	}

	delete[] this->grid;
}

int Grid::getSumOfSurroundedCells(unsigned short int i, unsigned short int j) {
	return this->getAt(i - 1, j - 1) + this->getAt(i - 1, j) +
		this->getAt(i - 1, j + 1) + this->getAt(i, j - 1) +
		this->getAt(i, j + 1) + this->getAt(i + 1, j - 1) +
		this->getAt(i + 1, j) + this->getAt(i + 1, j + 1);
}

void Grid::makeRow(string line, unsigned short int row, unsigned short int width) {
	for (unsigned short int i = 0; i < width; i++) {
		this->grid[row][i] = convertCharToInt(line[i]);

		// Checker for invalid input
		if (this->grid[row][i] != 1 && this->grid[row][i] != 0) {
			throw "Incorect input! Try Again";
			break;
		}
	}
}

unsigned short int Grid::getHeight() const {
	return this->height;
}

unsigned short int Grid::getWidth() const {
	return this->width;
}

int** Grid::getGrid() const {
	return this->grid;
}

void Grid::createGenarationZero() {
	bool thereIsError;
	string line;

	do {
		thereIsError = false;

		for (unsigned short int i = 0; i < this->getHeight(); i++) {
			// Reads line and try to convert it to row of the grid
			cin >> line;
			try {
				this->makeRow(line, i, this->getWidth());
			}
			catch (const char* msg) {
				cout << msg << endl;
				thereIsError = true;
				break;
			}
		}
	} while (thereIsError);
}

void Grid::makeNextGeneration() {
	// Makes new Grid because when we make new generation 
	// the old one has to be unchanged until we are done
	Grid temp(this->getHeight(), this->getWidth());

	int sumOfSurroundedCells;
	for (unsigned short int i = 0; i < this->getHeight(); i++) {
		for (unsigned short int j = 0; j < this->getWidth(); j++) {
			sumOfSurroundedCells = 0;

			if (this->getGrid()[i][j] == 1) {
				if (this->getSumOfSurroundedCells(i, j) == 2 ||
					this->getSumOfSurroundedCells(i, j) == 3 ||
					this->getSumOfSurroundedCells(i, j) == 6) {

					temp.getGrid()[i][j] = 1;
				}
				else {
					temp.getGrid()[i][j] = 0;
				}

			} else {
				if (this->getSumOfSurroundedCells(i, j) == 3 ||
					this->getSumOfSurroundedCells(i, j) == 6) {

					temp.getGrid()[i][j] = 1;
				}
				else {
					temp.getGrid()[i][j] = 0;
				}
			}
		}
	}

	*this = temp;
}