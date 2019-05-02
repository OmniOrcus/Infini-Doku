#pragma once


class GameConfig {
	//Singleton and Flyweight patterns
public:
	GameConfig(unsigned short _base);
	~GameConfig(); //Delete the options array
	static GameConfig* getConfig();
	static void reset();
	unsigned short getBase();
	unsigned int getRange();
	unsigned long getSlots();
	unsigned int* getOption(unsigned int option);

private:
	static GameConfig* singleton;
	unsigned short base; 
	unsigned int range; //base^2
	unsigned long slots; //range^2
	unsigned int *options;
	unsigned int empty = 0;


};

