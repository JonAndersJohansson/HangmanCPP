#pragma once // ANVÄND alltid i .h-filer. App.h inkluderas en gång per .cpp-fil

#include "StartScreen.h"
#include "GameLogic.h"
#include "GameGraphics.h"


class App { // DETTA är en .h-fil, alltså en header-fil som innehåller deklarationer av klassen App.
	        // Den innehåller inte implementationen, det gör .cpp-filen.
    private:
        StartScreen startScreen;
        GameLogic gameLogic;
        bool showStartScreenGraphics = true;

    public:
        App(StartScreen startScreen, GameLogic gameLogic);
        void Run();
};
