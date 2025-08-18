#pragma once // ANV�ND alltid i .h-filer. App.h inkluderas en g�ng per .cpp-fil

#include "StartScreen.h"
#include "GameLogic.h"
#include "GameGraphics.h"


class App { // DETTA �r en .h-fil, allts� en header-fil som inneh�ller deklarationer av klassen App.
	        // Den inneh�ller inte implementationen, det g�r .cpp-filen.
    private:
        StartScreen startScreen;
        GameLogic gameLogic;
        bool showStartScreenGraphics = true;

    public:
        App(StartScreen startScreen, GameLogic gameLogic);
        void Run();
};
