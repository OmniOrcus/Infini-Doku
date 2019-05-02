#pragma once

#include "Grid.h"

class GridValidator {

public:
	bool validate(Grid& grid);

private:
	bool filledCheck(Grid& grid);
	bool checkRows(Grid& grid);
	bool checkCols(Grid& grid);
	bool checkBoxs(Grid& grid);

};