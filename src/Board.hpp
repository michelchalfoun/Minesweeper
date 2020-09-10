#pragma once
#include <string>
#include "TileBehaviors.h"
using namespace std;

class Board{
private:
    Tile** tileArray2D;
public:
    Board();
    Board(string fileName);
    void importFromFile(string fileName);
    Tile** getBoardData();
    void randomizeBoard();
    void emptyBoard();
    void surroundingMineCounter(int X, int Y);
    void countAllMines();
    void tileLeftClick(int X, int Y);
    void tileRightClick(int X, int Y);
    int flagCounter();
    int mineCounter();
    ~Board();
};