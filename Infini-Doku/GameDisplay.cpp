
#include "stdafx.h"
#include "GameDisplay.h"
#include "GameConfig.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

//debug
#include <iostream>

GameDisplay::GameDisplay() {
	//Set cell width
	cellWidth = (((unsigned short)(log10(GameConfig::getConfig()->getRange()))) + 1);

	//set up row break
	rowBreak = "";
	unsigned short dashes = ((GameConfig::getConfig()->getRange() * (cellWidth + 1)) - 1) + ((GameConfig::getConfig()->getBase() - 1) * 2);

	//std::cerr << "w: " << cellWidth << " / d: " << dashes;

	for (unsigned short i = 0; i < dashes; i++) {
		rowBreak += "-";
	}
}

void GameDisplay::DisplayGrid(Grid& answerGrid) {
	std::cout << std::endl;
	for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) {
		if (row%GameConfig::getConfig()->getBase() == 0) {
			std::cout << rowBreak << std::endl;
		}
		for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {
			if (col%GameConfig::getConfig()->getBase() == 0 && col != 0) {
				std::cout << "| ";
			}
			if (answerGrid.getCell(row, col) == *GameConfig::getConfig()->getOption(0)) {
				for (unsigned short i = 0; i < cellWidth; i++) { std::cout << "_"; }
			}
			else { std::cout << uintFormat(answerGrid.getCell(row, col)); }
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	std::cout << rowBreak << std::endl;

}

std::string GameDisplay::uintFormat(const unsigned int number) {
	std::stringstream ss;
	ss << std::setw(cellWidth) << std::setfill('0') << number;
	return ss.str();
}