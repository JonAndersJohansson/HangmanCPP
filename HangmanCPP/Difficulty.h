#pragma once
#include <vector>
#include <string>          // eftersom vi använder vector<string>
#include "DisplayList.h"   // vi har en referens till DisplayList

class Difficulty {
private:
	std::vector<std::string> listOfDifficulties{
	"1. Easy", "2. Normal", "3. Hard"
	};

	DisplayList& displayList;

public:
	Difficulty(DisplayList& displayList);
	int ChooseGameDifficulty();

};