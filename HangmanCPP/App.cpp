#include "App.h"    //	Klistrar in klassens ritning

App::App(StartScreen startScreen, GameLogic gameLogic)  //	Konstruktorns implementering, med initialisering av fält
    : startScreen(startScreen), gameLogic(gameLogic) {
}

void App::Run() {   // Metodens kod – startar spelet 
    startScreen.StartScreenGraphics(showStartScreenGraphics); //Anropar metod på StartScreen    
    gameLogic.Game();                                         //Anropar metod på GameLogic
}
