#pragma once
#include "Grid.h"
#include "Move.h"
#include "IGridDisplay.h"
#include <List>
#include <string>


class GamePlay {
public:
	GamePlay(Grid& _answer, Grid& puzzle, IGridDisplay& _display, bool _displayCorrectCount);
	~GamePlay();
	void Loop();
private:
	Grid& answer;
	GameGrid gameBoard;
	IGridDisplay& display;
	std::list<Move*> moveRecord;
	unsigned long correctCount;
	bool displayCorrectCount;
	Move* constructMove(std::string input); //Moves constructed here are placed on the heap. This is risky, but they should be cleaned up by the Gameplay Deconstructor

};