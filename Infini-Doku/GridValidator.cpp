
#include "stdafx.h"
#include "GridValidator.h"
#include "GameConfig.h"

#include <iostream>

bool GridValidator::validate(Grid& grid) {
	if (filledCheck(grid)) {
		return (checkRows(grid) && checkCols(grid) && checkBoxs(grid));
	}
	return false;
}

bool GridValidator::filledCheck(Grid& grid) {

	for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) { 
		for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {
			if (grid.getCell(row, col) == 0) {
				std::cout << "Filled fail: " << row << "," << col << std::endl;
				return false;
			}
		} 
	}

	return true;

}

bool GridValidator::checkRows(Grid& grid) {

	bool* rowFlags = new bool[GameConfig::getConfig()->getRange()];

	for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) {

		for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
			rowFlags[i] = true;
		}

		for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {
			rowFlags[grid.getCell(row, col) - 1] = false;
		}

		for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
			if (rowFlags[i]) {
				std::cout << "Row fail: " << row << "->" << i << std::endl;
				return false;
			}
		}

	}

	delete[] rowFlags;

	return true;

}

bool GridValidator::checkCols(Grid& grid) {

	bool* colFlags = new bool[GameConfig::getConfig()->getRange()];

	for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {

		for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
			colFlags[i] = true;
		}

		for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) {
			colFlags[grid.getCell(row, col) - 1] = false;
		}

		for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
			if (colFlags[i]) {
				std::cout << "Col fail: " << col << "->" << i << std::endl;
				return false;
			}
		}

	}

	delete[] colFlags;

	return true;

}

bool GridValidator::checkBoxs(Grid& grid){

	bool* boxFlags = new bool[GameConfig::getConfig()->getRange()];
	unsigned long r0x;
	unsigned long c0x;

	for (unsigned short r0 = 0; r0 < GameConfig::getConfig()->getBase(); r0++) {
		r0x = r0 * GameConfig::getConfig()->getBase();
		for (unsigned short c0 = 0; c0 < GameConfig::getConfig()->getBase(); c0++) {
			c0x = c0 * GameConfig::getConfig()->getBase();
			//std::cout << std::endl << "box check: " << r0 << "," << c0 << std::endl;

			for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
				boxFlags[i] = true;
			}

			for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {

				//std::cout << r0x + i % GameConfig::getConfig()->getBase() << "-" << c0x + i / GameConfig::getConfig()->getBase() << ", ";
				boxFlags[grid.getCell(r0x + i / GameConfig::getConfig()->getBase(), c0x + i % GameConfig::getConfig()->getBase()) - 1] = false;
			}

			for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
				if (boxFlags[i]) {
					//std::cout << "box fail: " << col << "->" << i << std::endl;
					return false;
				}
			}

		}
	}

	delete[] boxFlags;

	return true;

}