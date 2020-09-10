#pragma once
#include <SFML/Graphics.hpp>

class Tile{
public:
    int X;
    int Y;
    bool revealed;
    bool flagged;
    bool dangerous;
    int minesCounter;
    Tile();
    Tile(int X, int Y, bool bomb);
    bool clickedBomb();
    bool correctReveal();
};