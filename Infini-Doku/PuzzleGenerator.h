#pragma once
#include <list>
#include <vector>


class Grid;

class PuzzleGenerator {

public:
	//PuzzleGenerator();
	//~PuzzleGenerator();
	void GeneratePuzzle(Grid& answerGrid);
	void GeneratePuzzle(Grid& answerGrid, unsigned int seed);
	void SetClues(Grid& answerGrid, Grid& puzzleGrid, float clueDensity = 0.4f);

private:
	void SetBaseGrid(Grid& answerGrid);
	void ShuffleGrid(Grid& answerGrid);
	//cellSwitcher
	unsigned int* holder = nullptr;
	void switchCells(Grid& answerGrid, unsigned long a, unsigned long b);
	void shiftRow(Grid& answerGrid, unsigned int row, bool shiftUp);
	void shiftCol(Grid& answerGrid, unsigned int col, bool shiftRight);
	void slideRow(Grid& answerGrid, unsigned int row, bool shiftUp);
	void slideCol(Grid& answerGrid, unsigned int col, bool shiftRight);
	//It would be faster to just swap the flyweight values in the config.
	//However that would break the encapsulation of roles.
	void swapValues(Grid& answerGrid, unsigned int a, unsigned int b);
	void populateOptions(std::list<int> &options);
	unsigned long selectStep(std::vector<unsigned int> &primes, unsigned long min, unsigned long max);;
};