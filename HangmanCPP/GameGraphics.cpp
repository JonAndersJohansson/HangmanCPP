#include "GameGraphics.h"

void GameGraphics::GraphicsOneLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         |     /|\\" << std::endl;
    std::cout << "                         |     / " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsTwoLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         |     /|\\" << std::endl;
    std::cout << "                         |     " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsThreeLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         |      |\\" << std::endl;
    std::cout << "                         |     " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsFourLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         |      |" << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsFiveLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsSixLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsZeroLives() const {
    std::cout << "                        ___________" << std::endl;
    std::cout << "                         |/     |" << std::endl;
    std::cout << "                         |      O" << std::endl;
    std::cout << "                         |     /|\\" << std::endl;
    std::cout << "                         |     / \\" << std::endl;
    std::cout << "                         | " << std::endl;
}

void GameGraphics::GraphicsLived() const {
    std::cout << "                            \\" << std::endl;
    std::cout << "                            /\\" << std::endl;
    std::cout << "                           /  \\           `" << std::endl;
    std::cout << "                          /    \\           \\O__" << std::endl;
    std::cout << "                         |             ~-\\_/_" << std::endl;
    std::cout << "                         |    --o             \\, " << std::endl;
}

void GameGraphics::ShowHangmanStatus(signed char lives) const {
    if (lives == 6)
        GraphicsSixLives();
    else if (lives == 5)
        GraphicsFiveLives();
    else if (lives == 4)
        GraphicsFourLives();
    else if (lives == 3)
        GraphicsThreeLives();
    else if (lives == 2)
        GraphicsTwoLives();
    else if (lives == 1)
        GraphicsOneLives();
    else if (lives == 0)
        GraphicsZeroLives();
    else
        std::cout << "Error in ShowHangmanStatus" << std::endl;
}

void GameGraphics::MainGraphics() const {
    std::cout << " _   _  _   _  _   _ _____   ___    _____ _   _____________ _____ " << std::endl;
    std::cout << "| | | |(_)_(_)| \\ | |  __ \\ / _ \\  |  __ \\ | | | ___ \\ ___ \\  ___|" << std::endl;
    std::cout << "| |_| | / _ \\ |  \\| | |  \\// /_\\ \\ | |  \\/ | | | |_/ / |_/ / |__  " << std::endl;
    std::cout << "|  _  |/ /_\\ \\| . ` | | __ |  _  | | | __| | | | ___ \\ ___ \\  __| " << std::endl;
    std::cout << "| | | ||  _  || |\\  | |_\\ \\| | | | | |_\\ \\ |_| | |_/ / |_/ / |___ " << std::endl;
    std::cout << "\\_| |_/\\_| |_/\\_| \\_/\\____/\\_| |_/  \\____/\\___/\\____/\\____/\\____/ " << std::endl;
    std::cout << "   You have 6 lifes. Guess the letters to find the right word." << std::endl;
}
