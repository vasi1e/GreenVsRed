#pragma once
#include <iostream>
#include <string>

using namespace std;

class Grid {
private:
	int** grid;
	unsigned short int height;
	unsigned short int width;

	int getSumOfSurroundedCells(unsigned short int i, unsigned short int j);
	void makeRow(string line, unsigned short int row, unsigned short int width);

public:
	Grid(unsigned short int _height, unsigned short int _width);
	Grid(const Grid& other);
	Grid& operator=(const Grid& other);
	~Grid();

	int getAt(unsigned short int x, unsigned short int y);

	unsigned short int getHeight() const;
	unsigned short int getWidth() const;
	int** getGrid() const;

	void makeNextGeneration();
	void createGenarationZero();
};