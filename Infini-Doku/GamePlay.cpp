#include "stdafx.h"
#include "GamePlay.h"
#include "GameConfig.h"
#include <iostream>
#include <sstream>
#include <string>

GamePlay::GamePlay(Grid& _answer, Grid& puzzle, IGridDisplay& _display, bool _displayCorrectCount) : answer(_answer), gameBoard(puzzle), display(_display) {
	moveRecord = std::list<Move*>();
	correctCount = 0;
	displayCorrectCount = _displayCorrectCount;
}

GamePlay::~GamePlay() {
	for (Move* move : moveRecord) {
		delete move;
	}
	moveRecord.clear();
}

Move* GamePlay::constructMove(std::string input) {
	unsigned int r,c,v,row,col,val;
	
	for (unsigned long i = 0; i < GameConfig::getConfig()->getSlots(); i++) {
		if (input[i] == ',') {
			r = i;
			break;
		}
	}

	for (unsigned long i = r+1; i < GameConfig::getConfig()->getSlots(); i++) {
		if (input[i] == '-') {
			c = i;
			break;
		}
	}

	row = std::stoul(input.substr(0, r)) - 1;
	col = std::stoul(input.substr(r + 1, c - r)) - 1;
	val = std::stoul(input.substr(c + 1, input.length() - c));

	//std::cout << "Reg=> " << row << "," << col << ":" << val;

	return new Move(row, col, val);

}

void GamePlay::Loop() {

	bool running = true;
	std::stringstream gameMenu;
	gameMenu << std::endl << "~Game Menu~" << std::endl << "1 - Enter Move" << std::endl << "2 - Undo Moves" << std::endl << "3 - Resign Game" << std::endl;
	int input;
	std::string strInput;
	Move* move = nullptr;

	while (running) {
		//main loop
		display.DisplayGrid(gameBoard.Read());

		if (displayCorrectCount) {
			std::cout << correctCount << " correct moves." << std::endl;
		}
		
		std::cout << gameMenu.str() << std::endl << "Select an option: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;

		switch (input) {
			case 1:
				//Enter Move
				std::cout << "enter your move[r,c-v]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> strInput;

				try {
					move = constructMove(strInput);

					if (move->Apply(gameBoard)) {
						if (move->getBackup() == answer.getCell(move->getRow(), move->getCol())) { correctCount--; }
						if (move->getPayload() == answer.getCell(move->getRow(), move->getCol())) { correctCount++; }
						moveRecord.push_back(move);
					}
					else {
						std::cout << "You can't modify that value." << std::endl;
						delete move;
					}

					if (correctCount >= gameBoard.getCorrectTarget()) {
						display.DisplayGrid(gameBoard.Read());
						std::cout << " ~ PUZZLE SOLVED! ~ " << std::endl;
						running = false;
					}
				}
				catch (const std::exception& e){
					std::cerr << e.what() << std::endl;
				}

				break;
			case 2: 
				//undo moves
				std::cout << "You have made " << moveRecord.size() << " moves." << std::endl << "How many would you like to undo: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> input;
				while (input > moveRecord.size() || input < 0) {
					std::cout << "You can at most remove " << moveRecord.size() << " moves." << std::endl << "How many would you like to undo: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> input;
				}

				for (unsigned int i = 0; i < input; i++) {
					move = moveRecord.back();
					if (move->Reverse(gameBoard)) {
						if (move->getBackup() == answer.getCell(move->getRow(), move->getCol())) { correctCount++; }
						if (move->getPayload() == answer.getCell(move->getRow(), move->getCol())) { correctCount--; }
						moveRecord.pop_back();
						delete move;
					}
					else {
						std::cerr << "Move Record is inconsistant with game state." << std::endl << "Returning to Main Menu." << std::endl;
						return;
					}
				}

				break;
			case 3:
				//resign game
				display.DisplayGrid(gameBoard.Read());
				display.DisplayGrid(answer);
				running = false;
				break;
			default:
				std::cout << input << " is not a valid option." << std::endl;
				break;
		}


	}

}