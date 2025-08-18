#include "StartScreen.h" //inkludera alltid sin header-fil
#include <iostream> // Ger tillgång till std::cout, std::endl osv – alltså utskrift till konsolen (samma som Console.WriteLine i C#)
#include <thread> // SE NEDAN
#include <chrono> // BEHÖVS FÖR: std::this_thread::sleep_for(std::chrono::milliseconds(100));
#include <conio.h>  // För _kbhit() och _getch() på Windows, LIKT Console.ReadKey()

StartScreen::StartScreen(GameGraphics& graphics) //Konstruktor  
    : gameGraphics(graphics) {
}

bool StartScreen::StartScreenGraphics(bool flag) {
    int itterationInStartGraphics = 6;

    while (!_kbhit()) {
        if (itterationInStartGraphics == -1)
            itterationInStartGraphics = 6;

        system("cls");
        gameGraphics.MainGraphics();
        std::cout << std::endl;
        gameGraphics.ShowHangmanStatus(itterationInStartGraphics);
        std::cout << std::endl;
        std::cout << "                  Press any key to play" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        itterationInStartGraphics--;
    }

    _getch();  // Väntar på att användaren trycker tangent
    return flag = false;
}
