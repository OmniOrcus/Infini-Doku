#pragma once
#include "Grid.h"

class GameGrid {
public:
	GameGrid(Grid& _grid);
	~GameGrid();
	Grid& Read();
	bool SetCell(unsigned int row, unsigned int col, unsigned int value);
	unsigned int getCorrectTarget();
private:
	Grid& grid;
	bool* mutabilityMatrix;
	unsigned int correctTarget;
};