#include "App.h" //Likt using namespace

int main() {
    GameGraphics graphics;              // Skapa GameGraphics????? Måste skicka med den?
	StartScreen startScreen(graphics);  //skapa StartScreen med GameGraphics
	DisplayList displayList(graphics);  // Skapa DisplayList
    Difficulty difficulty(displayList); // Skicka in det i konstruktorn
	WordGenerator wordGenerator;        // Skapa WordGenerator
    GameLogic gameLogic(graphics, wordGenerator, difficulty);

    App app(startScreen, gameLogic);
    app.Run();

	return 0; //main() måste returnera ett värde, 0 betyder att programmet avslutades utan fel.
}