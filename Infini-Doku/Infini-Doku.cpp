// Infini-Doku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DecimalDisplay.h"
#include "GameDisplay.h"
#include "Grid.h"
#include "GameConfig.h"
#include "PuzzleGenerator.h"
#include "GridValidator.h"
#include "GamePlay.h"
#include <iostream>
#include <string>

#include <stdlib.h>
#include <chrono>
#include <sstream>

#include <fstream>
#include <exception>

#define clueTarget 0.4
#define defaultBase 3
#define configFile  "config.ini"

GameConfig* loadConfig(std::string path) {

	try {
		std::ifstream ifstream;
		short input;
		ifstream.open(path);
		ifstream >> input;
		ifstream.close();
		return new GameConfig(input);
	}
	catch (std::exception ex) {
		std::cout << "new config";
		return new GameConfig(defaultBase);
	}

}

void saveConfig(std::string path, GameConfig& config) {

	try {
		std::ofstream ofstream;
		ofstream.open(path, std::ios::trunc);
		ofstream << config.getBase();
		ofstream.close();
	}
	catch (std::exception ex) {
		std::cout << "Save Failure";
	}

}

void Log(std::string string) {
	std::cerr << std::endl << string << std::endl;
}

unsigned int ConvertStrSeed(std::string seed) {
	unsigned int tally = 0;
	for (unsigned int i = 0; i < seed.length(); i++) {
		tally += (((unsigned int)(seed[i])) * (i+1));
	}
	return tally;
}

void RunGame() {

	//Set up variables
	GameConfig *config = loadConfig(configFile);
	Grid* answer, *puzzle;
	answer = new Grid();
	puzzle = new Grid();
	PuzzleGenerator generator;
	GridValidator validator;
	IGridDisplay *display = new GameDisplay();
	bool running = true, correctCount = false;
	int input;
	std::string strInput;

	//menu prints
	std::stringstream mainMenu;
	mainMenu << std::endl << "~Main Menu~" << std::endl << "1 - Play Game" << std::endl << "2 - Test Matrix Generation" << std::endl << "3 - Options" << std::endl << "4 - Quit Game" << std::endl;
	std::stringstream optionsMenu;
	optionsMenu << std::endl << "~Options Menu~" << std::endl << "1 - Change Base" << std::endl << "2 - Toggle Display Correct Count" << std::endl;

	std::cout << " ~ Welcome to Infini-Doku ~" << std::endl << "Current base is " << config->getBase() << std::endl;

	//Main Menu Loop
	while (running) {

		std::cout << mainMenu.str() << std::endl << "Select an option: ";
		std::cin >> input;
		GamePlay* game;

		switch (input) {
			case 1:
				//run game
				//Display a Matrix
				std::cout << "Enter your seed (0 for random): ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> strInput;

				if (strInput == "0") { generator.GeneratePuzzle(*answer); }
				else { generator.GeneratePuzzle(*answer, ConvertStrSeed(strInput)); }

				generator.SetClues(*answer, *puzzle, clueTarget);

				game = new GamePlay(*answer, *puzzle, *display, correctCount);
				game->Loop();
				delete game; 
				delete answer;
				delete puzzle;
				answer = new Grid();
				puzzle = new Grid();

				break;
			case 2:
				//Display a Matrix
				std::cout << "Enter your seed (0 for random): ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> strInput;

				std::chrono::microseconds t;

				if (strInput == "0") { 
					t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
					generator.GeneratePuzzle(*answer); 
				}
				else {
					t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
					generator.GeneratePuzzle(*answer, ConvertStrSeed(strInput)); 
				}
				t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()) - t;

				display->DisplayGrid(*answer);
				std::cout << "Generated in " << std::to_string(t.count()) << " microseconds." << std::endl;

				bool hide;
				hide = false;

				std::cout << "Hide parts of the matrix(1 or 0): ";;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> hide;

				if (hide) {
					t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
					generator.SetClues(*answer, *puzzle, clueTarget);
					t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()) - t;

					display->DisplayGrid(*puzzle);
					std::cout << "Hidden in " << std::to_string(t.count()) << " microseconds." << std::endl;
				}

				delete answer;
				delete puzzle;
				answer = new Grid();
				puzzle = new Grid();

				break;
			case 3: 
				//options
				std::cout << optionsMenu.str() << std::endl << "Select an option: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> input;

				switch (input) {
					case 1:
						//change base
						unsigned short base;
						std::cout << "Please enter the new base (2 or higher): ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin >> base;
						while (base < 2) {
							std::cout << "The new base must be greater then 1." << std::endl << "Please enter the new base (2 or higher): ";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cin >> base;
						}

						//delete old objects
						delete config;
						delete display;
						delete puzzle;
						delete answer;
						//Reconstruct objects
						config = new GameConfig(base);
						display = new GameDisplay();
						puzzle = new Grid();
						answer = new Grid();

						std::cout << "The new base is " << config->getBase() << std::endl;

						break;
					case 2:
						//toggle correct display
						correctCount = !correctCount;
						std::cout << "Display Correct Count = " << correctCount << std::endl;
						break;
					default:
						std::cout << input << " is not a vaild option." << std::endl << "Returning to main menu." << std::endl;
						break;
				}

				break;
			case 4:
				//quit
				running = false;
				break;
			default:
				//invalid input handle
				std::cout << input << " is not a vaild option." << std::endl;
				break;
		}

	}

	saveConfig(configFile, *config);

	//Clean up
	delete display;
	delete config;
	delete answer;
	delete puzzle;

}

void RunTest() {

	unsigned short base;
	std::cout << "Base: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> base;

	//Instantiate Config
	GameConfig config = GameConfig(base);
	Log("config set");

	Grid grid;
	Grid puzzle;
	PuzzleGenerator generator;
	GridValidator validator;
	IGridDisplay *display = new DecimalDisplay();

	Log("objects instantiated");

	unsigned int seed;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter Seed: ";
	std::cin >> seed;


	std::chrono::microseconds t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (seed == 0) { generator.GeneratePuzzle(grid); }
	else { generator.GeneratePuzzle(grid, seed); }
	t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()) - t;



	Log("puzzle generated: " + std::to_string(t.count()) + " microseconds");

	Log("Validate: " + std::to_string(validator.validate(grid)));

	display->DisplayGrid(grid);
	Log("answer displayed");

	generator.SetClues(grid, puzzle, clueTarget);
	Log("set clues");

	display->DisplayGrid(puzzle);
	Log("puzzle displayed");

	delete display;
	Log("display deleted");

	int x;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> x;

}

int main()
{

	//RunTest();
	RunGame();

    return 0;
}

