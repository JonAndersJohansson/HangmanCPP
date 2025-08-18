#pragma once
#include <iostream>

class GameGraphics {
public:
    void GraphicsOneLives() const;
    void GraphicsTwoLives() const;
    void GraphicsThreeLives() const;
    void GraphicsFourLives() const;
    void GraphicsFiveLives() const;
    void GraphicsSixLives() const;
    void GraphicsZeroLives() const;
    void GraphicsLived() const;

    void ShowHangmanStatus(signed char lives) const;
    void MainGraphics() const;
};
