#include "DisplayList.h"
#include <vector>
#include <string>  #include <conio.h> // för _getch()
#include <conio.h>

DisplayList::DisplayList(GameGraphics& graphics) //Konstruktor  
    : gameGraphics(graphics) {
}

int DisplayList::BrowseList(const std::vector<std::string>& list) {
    int selectedIndex = 0;

    while (true) {
        system("cls");
        gameGraphics.MainGraphics();
        gameGraphics.GraphicsSixLives();
        std::cout << std::endl;
        std::cout << "Choose difficulty with arrows and press Enter\n" << std::endl;

        for (size_t i = 0; i < list.size(); ++i) {
            if (i == selectedIndex)
                std::cout << "> " << list[i] << " <\n";
            else
                std::cout << "  " << list[i] << "\n";
        }

        int key = _getch(); // läs tangent utan att visa den

        if (key == 224) { // 224 signalerar specialtangent (som pilar)
            int arrow = _getch(); // läs vilken tangent

            if (arrow == 72) { // Up arrow
                selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : list.size() - 1;
            }
            else if (arrow == 80) { // Down arrow
                selectedIndex = (selectedIndex < list.size() - 1) ? selectedIndex + 1 : 0;
            }
        }
        else if (key == 13) { // Enter
            return selectedIndex;
        }
    }
}