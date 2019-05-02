#pragma once
#include "IGridDisplay.h"
#include <String>

class GameDisplay : public IGridDisplay {
public:
	GameDisplay();
	void DisplayGrid(Grid& answerGrid);

private:
	std::string rowBreak;
	unsigned short cellWidth;
	std::string uintFormat(const unsigned int number);

};