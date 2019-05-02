#include "stdafx.h"
#include "Move.h"

Move::Move(unsigned int _row, unsigned int _col, unsigned _payload) {
	row = _row;
	col = _col;
	payload = _payload;
	backUp = 0;
}

bool Move::Apply(GameGrid& grid) {
	backUp = grid.Read().getCell(row, col);
	return grid.SetCell(row, col, payload);
}

bool Move::Reverse(GameGrid& grid) {
	if (grid.Read().getCell(row, col) == payload) {
		return grid.SetCell(row, col, backUp);
	}
	return false;
}

unsigned int Move::getRow() { return row; }
unsigned int Move::getCol() { return col; }
unsigned int Move::getPayload() { return payload; }
unsigned int Move::getBackup() { return backUp; }