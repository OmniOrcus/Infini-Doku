
#include "stdafx.h"
#include "Grid.h"
#include "GameConfig.h"

Grid::Grid() {
	//Instantiate grid
	grid = new unsigned int*[GameConfig::getConfig()->getSlots()];
	//Assign initilization values to the grid.
	for (unsigned long i = 0; i < GameConfig::getConfig()->getSlots(); i++) {
		grid[i] = GameConfig::getConfig()->getOption(0);
	}
}

Grid::~Grid() {
	delete grid;
}

unsigned int Grid::getCell(unsigned int row, unsigned int col) {
	return *grid[(row * GameConfig::getConfig()->getRange()) + col];
}