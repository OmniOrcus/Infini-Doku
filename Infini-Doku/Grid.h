#pragma once
#include "PuzzleGenerator.h"
#include "GameGrid.h"



class Grid {

	friend class PuzzleGenerator;
	friend class GameGrid;

public:
	Grid();
	~Grid();
	unsigned int getCell(unsigned int row, unsigned int col);

private:
	unsigned int** grid;

};