#pragma once
#include "GameGraphics.h"

class StartScreen {
private:
    GameGraphics& gameGraphics;

public:
	StartScreen(GameGraphics& graphics); // & referens f�r att undvika kopiering
    bool StartScreenGraphics(bool flag);
};
