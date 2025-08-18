#include "Difficulty.h"
#include <vector>
#include <string>  
#include <thread>

Difficulty::Difficulty(DisplayList& displayList)
    : displayList(displayList) {
}

int Difficulty::ChooseGameDifficulty() {
    int choice = displayList.BrowseList(listOfDifficulties);

    switch (choice) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    default:
        std::cout << "Error in difficulty, try again." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return 0;
    }
}