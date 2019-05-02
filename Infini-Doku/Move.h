#pragma once

#include "GameGrid.h"

class Move{

public:
	Move(unsigned int _row, unsigned int _col, unsigned _payload);
	bool Apply(GameGrid& grid);
	bool Reverse(GameGrid& grid);
	unsigned int getRow();
	unsigned int getCol();
	unsigned int getPayload();
	unsigned int getBackup();
private:
	unsigned int row, col, payload, backUp;

};