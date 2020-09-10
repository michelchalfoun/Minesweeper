#include "TileBehaviors.h"

Tile::Tile() {
    X = 0;
    Y = 0;
    revealed = false;
    flagged = false;
    dangerous = false;
    minesCounter = 0;
}

Tile::Tile(int X, int Y, bool bomb) {
    this->X = X;
    this->Y = Y;
    revealed = false;
    flagged = false;
    dangerous = bomb;
    minesCounter = 0;
}

bool Tile::clickedBomb() {
    if(revealed && dangerous){
        return true;
    }
}

bool Tile::correctReveal() {
    return (revealed == !dangerous);
}