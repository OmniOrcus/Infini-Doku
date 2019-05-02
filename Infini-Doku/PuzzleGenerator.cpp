
#include "stdafx.h"
#include "PuzzleGenerator.h"
#include "GameConfig.h"
#include "Grid.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <list>
#define minStep 2

//DEBUG
#include <iostream>

void PuzzleGenerator::GeneratePuzzle(Grid& answerGrid) {
	GeneratePuzzle(answerGrid, time(0));
}

void PuzzleGenerator::GeneratePuzzle(Grid& answerGrid, unsigned int seed) {
	
	//initilize random seed
	srand(seed);

	//setup initial grid
	SetBaseGrid(answerGrid);
	ShuffleGrid(answerGrid);
	/*
	for (unsigned int i = 0; i < (std::rand() % GameConfig::getConfig()->getBase()) + 1; i++) {
		swapValues(answerGrid, std::rand() % GameConfig::getConfig()->getRange(), std::rand() % GameConfig::getConfig()->getRange());
	}//*/


	/*
	//DEBUG
	//Shift Row Tests
	shiftRow(answerGrid, 0, true);
	shiftRow(answerGrid, 0, false);
	shiftRow(answerGrid, 2, true);
	shiftRow(answerGrid, 2, false);
	shiftRow(answerGrid, 3, true);
	shiftRow(answerGrid, 3, false);
	shiftRow(answerGrid, 5, true);
	shiftRow(answerGrid, 5, false);
	shiftRow(answerGrid, 6, true);
	shiftRow(answerGrid, 6, false);//*/
	/*
	//Shift Col Tests
	shiftCol(answerGrid, 0, true);
	shiftCol(answerGrid, 0, false);
	shiftCol(answerGrid, 2, true);
	shiftCol(answerGrid, 2, false);
	shiftCol(answerGrid, 3, true);
	shiftCol(answerGrid, 3, false);
	shiftCol(answerGrid, 5, true);
	shiftCol(answerGrid, 5, false);
	shiftCol(answerGrid, 6, true);
	shiftCol(answerGrid, 6, false);//*/
	/*
	//Slide Row Tests
	slideRow(answerGrid, 0, true);
	slideRow(answerGrid, 0, false);
	slideRow(answerGrid, 2, true);
	slideRow(answerGrid, 2, false);//*/
	/*
	//Slide Col Tests
	slideCol(answerGrid, 0, true);
	slideCol(answerGrid, 0, false);
	slideCol(answerGrid, 2, true);
	slideCol(answerGrid, 2, false);//*/



}

void PuzzleGenerator::SetBaseGrid(Grid& answerGrid) {

	/*unsigned long rowComponent;
	for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) {
		rowComponent = (row * GameConfig::getConfig()->getRange()); //optimization: rowComponet calced once.
		for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {
			answerGrid.grid[rowComponent + col] = GameConfig::getConfig()->getOption((((row / GameConfig::getConfig()->getBase()) + ((row % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase()) + col) % GameConfig::getConfig()->getRange()) + 1);
		}
	}*/

	//Construct list of prime factors
	std::vector<unsigned int> primes = std::vector<unsigned int>();
	//fill with factors
	for (int i = 2; i < GameConfig::getConfig()->getBase(); i++) {
		if (GameConfig::getConfig()->getBase() % i == 0) {
			primes.push_back(i);
		}
	}
	primes.push_back(GameConfig::getConfig()->getBase());

	//std::cout << std::endl;
	//cull non-primes
	for (int i = primes.size() - 1; i >= 0; i--) {
		for (int j = 0; j < primes.size(); j++) {
			if (primes[i] % primes[j] == 0 && i != j) { 
				primes.erase(primes.begin() + i);
				break;
			}
		}
	}

	//Select a valid step
	unsigned int step = selectStep(primes, minStep, GameConfig::getConfig()->getRange());

	/*std::cout << "Step Debug: " << step << " ~ ";
	for (unsigned int prime : primes) {
		std::cout << prime << ", ";
	}
	std::cout << std::endl;*/

	unsigned long rowComponent;
	for (unsigned int row = 0; row < GameConfig::getConfig()->getRange(); row++) {
		rowComponent = (row * GameConfig::getConfig()->getRange()); //optimization: rowComponet calced once.
		for (unsigned int col = 0; col < GameConfig::getConfig()->getRange(); col++) {
			answerGrid.grid[rowComponent + col] = GameConfig::getConfig()->getOption(((((((row / GameConfig::getConfig()->getBase()) + ((row % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase()) + col) % GameConfig::getConfig()->getRange())) * step) % GameConfig::getConfig()->getRange()) + 1);
		}
	}

}

void PuzzleGenerator::ShuffleGrid(Grid& answerGrid) {

	//set up
	bool direction;
	unsigned short shifts;

	//shifts
	for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
		direction = (bool)(rand() % 2);
		for (shifts = 0; shifts < rand() % GameConfig::getConfig()->getBase(); shifts++) {
			shiftRow(answerGrid, i, direction);
		}
		direction = (bool)(rand() % 2);
		for (shifts = 0; shifts < rand() % GameConfig::getConfig()->getBase(); shifts++) {
			shiftCol(answerGrid, i, direction);
		}
	}

	//slides
	for (unsigned int i = 0; i < GameConfig::getConfig()->getBase(); i++) {
		direction = (bool)(rand() % 2);
		for (shifts = 0; shifts < rand() % GameConfig::getConfig()->getBase(); shifts++) {
			slideRow(answerGrid, i, direction);
		}
		direction = (bool)(rand() % 2);
		for (shifts = 0; shifts < rand() % GameConfig::getConfig()->getBase(); shifts++) {
			slideCol(answerGrid, i, direction);
		}
	}

}

void PuzzleGenerator::switchCells(Grid& answerGrid, unsigned long a, unsigned long b) {
	holder = answerGrid.grid[a];
	answerGrid.grid[a] = answerGrid.grid[b];
	answerGrid.grid[b] = holder;
	holder = nullptr;
}

void PuzzleGenerator::shiftRow(Grid& answerGrid, unsigned int row, bool shiftUp) {
	unsigned long a0 = row * GameConfig::getConfig()->getRange();
	unsigned long b0;

	unsigned int row0 = (row / GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase();

	if (shiftUp) {
		b0 = (((row+ GameConfig::getConfig()->getBase() -1)%GameConfig::getConfig()->getBase()) + row0) * GameConfig::getConfig()->getRange();
	}
	else {
		b0 = (((row + 1) % GameConfig::getConfig()->getBase()) + row0) * GameConfig::getConfig()->getRange();
	}

	for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
		//std::cout << std::endl << *answerGrid.grid[a0 + i] << "," << *answerGrid.grid[b0 + i];
		switchCells(answerGrid, (a0 + i), (b0 + i));
		//std::cout << "->" << *answerGrid.grid[a0 + i] << "," << *answerGrid.grid[b0 + i] << std::endl;
	}

}

void PuzzleGenerator::shiftCol(Grid& answerGrid, unsigned int col, bool shiftRight) {
	unsigned int a0 = col;
	unsigned int b0;

	if (shiftRight) {
		b0 = ((col + 1) % GameConfig::getConfig()->getBase()) + ((col / GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase());
	}
	else {
		b0 = ((col + GameConfig::getConfig()->getBase() - 1) % GameConfig::getConfig()->getBase()) + ((col / GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase());
	}

	//std::cout << std::endl << "Col: " << col << ", " << shiftRight << std::endl;
	for (unsigned long i = 0; i < GameConfig::getConfig()->getSlots(); i += GameConfig::getConfig()->getRange()) {
		//std::cout << std::endl << (a0+i) << "," << (b0 + i) << " ~ "<< *answerGrid.grid[a0 + i] << "," << *answerGrid.grid[b0 + i] << std::endl;
		switchCells(answerGrid, i + a0, i + b0);
	}		
}

void PuzzleGenerator::slideRow(Grid& answerGrid, unsigned int row, bool shiftUp) {
	unsigned long a0 = row * GameConfig::getConfig()->getBase() * GameConfig::getConfig()->getRange();
	unsigned long b0;

	if (shiftUp) {
		b0  = ((row + GameConfig::getConfig()->getBase() -1) % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase() * GameConfig::getConfig()->getRange();
	}
	else {
		b0 = ((row + 1) % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase() * GameConfig::getConfig()->getRange();
	}

	for (unsigned long i = 0; i < GameConfig::getConfig()->getRange() * GameConfig::getConfig()->getBase(); i++) {
		switchCells(answerGrid, a0+i, b0+i);
	}

}

void PuzzleGenerator::slideCol(Grid& answerGrid, unsigned int col, bool shiftRight) {
	unsigned long a0 = col * GameConfig::getConfig()->getBase();
	unsigned long b0;

	if (shiftRight) {
		b0 = ((col + 1) % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase();
	}
	else {
		b0 = ((col + GameConfig::getConfig()->getBase() - 1) % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase();
	}

	for (unsigned short i = 0; i < GameConfig::getConfig()->getBase(); i++) {
		for (unsigned long j = 0; j < GameConfig::getConfig()->getSlots(); j += GameConfig::getConfig()->getRange()) {
			switchCells(answerGrid, i + j + a0, i + j + b0);
		}
	}

}

void PuzzleGenerator::swapValues(Grid& answerGrid, unsigned int a, unsigned int b) {

	unsigned long aIndex, bIndex;
	unsigned int r0, c0;
	bool aFound, bFound;

	//std::cout << std::endl << "swaping values: " << a << " <-> " << b << std::endl;

	for (unsigned int i = 0; i < GameConfig::getConfig()->getRange(); i++) {
		aFound = false;
		bFound = false;
		r0 = (i / GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase();
		c0 = (i % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase();
		//std::cout << "scan roots: " << r0 << ", " << c0 << std::endl;
		for (unsigned int j = 0; j < GameConfig::getConfig()->getRange(); j++) {
			if (answerGrid.getCell(r0 + (j / GameConfig::getConfig()->getBase()), c0 + (j % GameConfig::getConfig()->getBase())) == a) {
				aIndex = ((r0 + (j / GameConfig::getConfig()->getBase())) * GameConfig::getConfig()->getRange()) + (c0 + (j % GameConfig::getConfig()->getBase()));
				aFound = true;
			}
			if (answerGrid.getCell(r0 + (j / GameConfig::getConfig()->getBase()), c0 + (j % GameConfig::getConfig()->getBase())) == b) {
				bIndex = ((r0 + (j / GameConfig::getConfig()->getBase())) * GameConfig::getConfig()->getRange()) + (c0 + (j % GameConfig::getConfig()->getBase()));
				bFound = true;
			}
			if (aFound && bFound) {
				break;
			}
		}

		//std::cout << "switching: " << aIndex << " <-> " << bIndex << std::endl;
		switchCells(answerGrid, aIndex, bIndex);

	}

}

void PuzzleGenerator::SetClues(Grid& answerGrid, Grid& puzzleGrid, float clueDensity) {

	for (unsigned long i = 0; i < GameConfig::getConfig()->getSlots(); i++) {
		puzzleGrid.grid[i] = answerGrid.grid[i];
		//std::cout << *puzzleGrid.grid[i] << ", " << *answerGrid.grid[i] << "; ";
	}

	float hidden = 0;
	unsigned int row = 0;
	unsigned int col = 0;

	/*Hide until at density
	while (1.0f - (hidden / GameConfig::getConfig()->getSlots()) > clueDensity) {

		std::cout << (1.0f - (hidden / GameConfig::getConfig()->getSlots())) << "; ";

		row = rand() % GameConfig::getConfig()->getRange();
		col = rand() % GameConfig::getConfig()->getRange();

		if (puzzleGrid.getCell(row, col) != *GameConfig::getConfig()->getOption(0)) {
			puzzleGrid.grid[(row * GameConfig::getConfig()->getRange()) + col] = GameConfig::getConfig()->getOption(0);
			hidden++;
		}

	}//*/


	//Construct list of prime factors
	std::vector<unsigned int> primes = std::vector<unsigned int>();
	//fill with factors
	for (int i = 2; i < GameConfig::getConfig()->getRange(); i++) {
		if (GameConfig::getConfig()->getRange() % i == 0) {
			primes.push_back(i);
		}
	}
	primes.push_back(GameConfig::getConfig()->getRange());

	//std::cout << std::endl;
	//cull non-primes
	for (int i = primes.size() - 1; i >= 0; i--) {
		for (int j = 0; j < primes.size(); j++) {
			if (primes[i] % primes[j] == 0 && i != j) {
				primes.erase(primes.begin() + i);
				break;
			}
		}
	}

	//step select
	unsigned int step = selectStep(primes, minStep, GameConfig::getConfig()->getSlots());

	unsigned int* store = nullptr;
	unsigned long index = step;
	std::list<int> options = std::list<int>();

	unsigned long failCount = 0;

	while (1.0f - (hidden / GameConfig::getConfig()->getSlots()) > clueDensity) {

		index += step;
		index %= GameConfig::getConfig()->getSlots();

		if (puzzleGrid.grid[index] != GameConfig::getConfig()->getOption(0)) {
			store = puzzleGrid.grid[index];
			puzzleGrid.grid[index] = GameConfig::getConfig()->getOption(0);

			//perform check
			populateOptions(options);

			unsigned int i;
			for (i = 0; i < GameConfig::getConfig()->getRange(); i++) {
				options.remove(*puzzleGrid.grid[((index / GameConfig::getConfig()->getRange()) * GameConfig::getConfig()->getRange()) + i]);
				options.remove(*puzzleGrid.grid[(i * GameConfig::getConfig()->getRange()) + (index % GameConfig::getConfig()->getRange())]);
				options.remove(*puzzleGrid.grid[(((((index / GameConfig::getConfig()->getRange()) /GameConfig::getConfig()->getBase())*GameConfig::getConfig()->getBase()) + (i/ GameConfig::getConfig()->getBase())) * GameConfig::getConfig()->getRange()) + ((((index % GameConfig::getConfig()->getRange()) / GameConfig::getConfig()->getBase())*GameConfig::getConfig()->getBase()) + (i % GameConfig::getConfig()->getBase()))]);
				//options.remove(*puzzleGrid.grid[((((row % GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase()) + (i % GameConfig::getConfig()->getBase())) * GameConfig::getConfig()->getRange()) + ((((col / GameConfig::getConfig()->getBase()) * GameConfig::getConfig()->getBase()) + (i % GameConfig::getConfig()->getBase())))]);
			}

			if (options.size() == 1) {
				hidden++;
				failCount = 0;
				//std::cout << "Hidding success: " << (index / GameConfig::getConfig()->getRange()) << ", " << (index % GameConfig::getConfig()->getRange()) << " => " << options.front() << " ~ " << hidden << std::endl;
				//std::cout << "Step Change: " << step;
				step = selectStep(primes, minStep, GameConfig::getConfig()->getSlots());
				//std::cout << " -> " << step << std::endl;
			}
			else {
				//std::cout << "Hidding Backktrack: " << index << " - " << (index / GameConfig::getConfig()->getRange()) << ", " << (index % GameConfig::getConfig()->getRange()) << " => " << options.size() << std::endl;
				puzzleGrid.grid[index] = store;
				failCount++;
				if (failCount >= GameConfig::getConfig()->getSlots()) {
					//std::cout << "Dumping: " << 1.0f - (hidden / GameConfig::getConfig()->getSlots()) << std::endl;
					return;
				}
			}

		}

		//Select value
		//if not empty-> remember and remove value;
		//if there are other safe options, replace removed values


	}

}
	
void PuzzleGenerator::populateOptions(std::list<int> &options) {
	options.clear();
	for (unsigned int i = 1; i <= GameConfig::getConfig()->getRange(); i++) {
		options.push_back(*GameConfig::getConfig()->getOption(i));
	}
}

unsigned long PuzzleGenerator::selectStep(std::vector<unsigned int> &primes, unsigned long min, unsigned long max) {

	//select step
	unsigned long step = (rand() % (max - min)) + min;
	bool checking = true;
	while (checking) {
		checking = false;
		for (unsigned int prime : primes) {
			if (step % prime == 0) {
				step = (rand() % (max - min)) + min;
				checking = true;
				break;
			}
		}
	}

	return step;

}