#include "stdafx.h"
#include "GameGrid.h"
#include "GameConfig.h"

#include <iostream>

GameGrid::GameGrid(Grid& _grid) : grid(_grid) {
	mutabilityMatrix = new bool[GameConfig::getConfig()->getSlots()];
	correctTarget = 0;

	for (unsigned long i = 0; i < GameConfig::getConfig()->getSlots(); i++) {
		if (grid.grid[i] == GameConfig::getConfig()->getOption(0)) {
			mutabilityMatrix[i] = true;
			correctTarget++;
		}
		else {
			mutabilityMatrix[i] = false;
		}
	}

}

GameGrid::~GameGrid(){
	delete[] mutabilityMatrix;
}

bool GameGrid::SetCell(unsigned int row, unsigned int col, unsigned int value) {
	unsigned long index = (row * GameConfig::getConfig()->getRange()) + col;
	if (mutabilityMatrix[index]) {
		grid.grid[index] = GameConfig::getConfig()->getOption(value);
		return true;
	}
	return false;
}

Grid& GameGrid::Read() {
	return grid;
}

unsigned int GameGrid::getCorrectTarget() { return correctTarget; }