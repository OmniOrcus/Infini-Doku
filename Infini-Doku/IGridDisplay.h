#pragma once
#include "Grid.h"

class IGridDisplay {

public:
	virtual void DisplayGrid(Grid& grid) = 0;
};