
#include "stdafx.h"
#include "GameConfig.h"
#define defaultBase 3

#include <iostream> //debug

GameConfig* GameConfig::singleton = nullptr;

GameConfig::GameConfig(unsigned short _base) {

	if (singleton == nullptr) {
		singleton = this;
		//std::cout << "singleton Set! " << ((int)_base);
	}

	//Basic values
	base = _base;
	range = base * base;
	slots = range * range;

	//options
	options = new unsigned int[range];
	for (unsigned int i = 0; i < range; i++) {
		options[i] = (i + 1);
	}
	//std::cout << " config constructed ";
}

GameConfig::~GameConfig() {
	//std::cout << "Deleting Config " << base;
	delete[] options;
	if (this == singleton) {
		singleton = nullptr;
	}
	
	
}

GameConfig* GameConfig::getConfig() {
	if (singleton == nullptr) {
		//std::cout << " Mising Singleton. ";
		singleton = new GameConfig(defaultBase);
	}
	return singleton;
}

//This should not be used, with only a few exceptions
void GameConfig::reset() {
	delete singleton;
	singleton = nullptr;
}

unsigned short GameConfig::getBase() {
	return base;
}

unsigned int GameConfig::getRange() {
	return range;
}

unsigned long GameConfig::getSlots() {
	return slots;
}

unsigned int* GameConfig::getOption(unsigned int option) {
	if (option == 0) {
		return &empty;
	}
	else {
		return &options[option - 1];
	}
}