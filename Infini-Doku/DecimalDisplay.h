#pragma once
#include "IGridDisplay.h"
#include <String>

class DecimalDisplay : public IGridDisplay {
public:
	DecimalDisplay();
	void DisplayGrid(Grid& answerGrid);

private:
	std::string rowBreak;
	unsigned short cellWidth;
	std::string uintFormat(const unsigned int number);

};