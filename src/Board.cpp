#include "Board.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Board::Board() {
    tileArray2D = new Tile* [25];
    for (int i = 0; i < 25; i++){
        tileArray2D[i] = new Tile[16];
        for(int j = 0; j < 16; j++){
            tileArray2D[i][j].dangerous =  0;
        }
    }
}

Board::Board(string fileName) {
    tileArray2D = new Tile* [25];
    for (int i = 0; i < 25; i++){
        tileArray2D[i] = new Tile[16];
    }
    importFromFile(fileName);
    countAllMines();
}

void Board::importFromFile(string fileName) {
    emptyBoard();
    ifstream testFile(fileName);
    if (testFile.is_open()){
        string line[16];
        int i = 0;
        while (getline(testFile, line[i])){
            i++;
        }
        for (int k = 0; k < 25; k++){
            for (int j = 0; j < 16; j++){
                tileArray2D[k][j].dangerous = (line[j][k] != '0');
            }
        }
        testFile.close();
    }
    countAllMines();
}

Tile **Board::getBoardData() {
    return tileArray2D;
}

Board::~Board() {
    for (int i = 0; i < 25; i++){
        delete tileArray2D[i];
    }
    delete tileArray2D;
}

void Board::randomizeBoard() {
    emptyBoard();
    bool chosenLocations[25][16];
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            chosenLocations[i][j] = false;
        }
    }
    srand(time(0));
    int counter = 0;
    while (counter < 50){
        int randX = rand() % 25;
        int randY = rand() % 16;
        if(!chosenLocations[randX][randY]){
            chosenLocations[randX][randY] = true;
            tileArray2D[randX][randY].dangerous = true;
            counter++;
        }
    }
    countAllMines();
}

void Board::emptyBoard() {
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            tileArray2D[i][j].dangerous = false;
            tileArray2D[i][j].revealed = false;
            tileArray2D[i][j].flagged = false;
            tileArray2D[i][j].minesCounter = 0;
        }
    }
}

void Board::surroundingMineCounter(int X, int Y) {
    int counter = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(!(i == 0 && j == 0)) {
                int tempX = X + i;
                int tempY = Y + j;
                if (tempX < 25 && tempX >= 0 && tempY < 16 && tempY >= 0) {
                    if (tileArray2D[tempX][tempY].dangerous) {
                        counter++;
                    }
                }
            }
        }
    }
    if (!(tileArray2D[X][Y].dangerous)) {
        tileArray2D[X][Y].minesCounter = counter;
    }
}

void Board::countAllMines() {
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            surroundingMineCounter(i,j);
        }
    }
}

void Board::tileLeftClick(int X, int Y) {
    if(!(tileArray2D[X][Y].flagged)) {
        if (tileArray2D[X][Y].dangerous) {
            tileArray2D[X][Y].revealed = true;
        }
        else if(!(tileArray2D[X][Y].revealed)) {
            tileArray2D[X][Y].revealed = true;
            if(tileArray2D[X][Y].minesCounter == 0){
                for(int i = -1; i < 2; i++){
                    for(int j = -1; j < 2; j++){
                        if(!(i == 0 && j == 0)) {
                            int tempX = X + i;
                            int tempY = Y + j;
                            if (tempX < 25 && tempX >= 0 && tempY < 16 && tempY >= 0) {
                                tileLeftClick(tempX,tempY);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Board::tileRightClick(int X, int Y) {
    if(!(tileArray2D[X][Y].revealed)){
        if(!(tileArray2D[X][Y].flagged)){
            tileArray2D[X][Y].flagged = true;
        }else{
            tileArray2D[X][Y].flagged = false;
        }
    }
}

int Board::flagCounter() {
    int counter = 0;
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            if (tileArray2D[i][j].flagged){
                counter++;
            }
        }
    }
    return counter;
}

int Board::mineCounter() {
    int counter = 0;
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 16; j++){
            if (tileArray2D[i][j].dangerous){
                counter++;
            }
        }
    }
    return counter;
}
