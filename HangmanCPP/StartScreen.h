#pragma once
#include "GameGraphics.h"

class StartScreen {
private:
    GameGraphics& gameGraphics;

public:
	StartScreen(GameGraphics& graphics); // & referens för att undvika kopiering
    bool StartScreenGraphics(bool flag);
};
