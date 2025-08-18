#pragma once
#include <vector>
#include <string>  
#include "GameGraphics.h"

class DisplayList {
private:
    GameGraphics& gameGraphics;

public:
    DisplayList(GameGraphics& graphics); // & referens f�r att undvika kopiering
    int BrowseList(const std::vector<std::string>& list);

};