#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameGraphics.h"
#include "WordGenerator.h"
#include "Difficulty.h"

class GameLogic {
private:
    GameGraphics& gameGraphics; 
    WordGenerator& wordGenerator;
	Difficulty& difficulty;

public:
    GameLogic(GameGraphics& graphics, WordGenerator& generator, Difficulty& diff);
    void Game();
};
