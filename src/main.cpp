#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <iostream>
#include "Board.hpp"
#include "TextureHandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    std::map<std::string, sf::Texture> allTextures;
    setTextures(allTextures);

    Board mainBoard;
    mainBoard.randomizeBoard();

    bool gameEnded = false;
    bool gameWon = false;
    bool debugMode = false;

    short boardWidth = 25;
    short boardHeight = 16;
    short tilePixelLength = 32;

    int mineStatus;

    sf::Sprite face;
    face.setTexture(allTextures["faceHappy"]);
    sf::Sprite winFace;
    winFace.setTexture(allTextures["faceWin"]);
    sf::Sprite loseFace;
    loseFace.setTexture(allTextures["faceLose"]);
    sf::Sprite debug;
    debug.setTexture(allTextures["debug"]);
    sf::Sprite test1;
    test1.setTexture(allTextures["test1"]);
    sf::Sprite test2;
    test2.setTexture(allTextures["test2"]);
    sf::Sprite test3;
    test3.setTexture(allTextures["test3"]);

    sf::Sprite minus;
    minus.setTexture(allTextures["minus"]);
    minus.setPosition(0, tilePixelLength * boardHeight);

    sf::Sprite digits[10];

    for(int i = 0; i < 10; i++){
        digits[i].setTexture(allTextures["digit" + to_string(i)]);
    }

    face.setPosition(368, 512);
    loseFace.setPosition(368, 512);
    winFace.setPosition(368, 512);
    debug.setPosition(496,512);
    test1.setPosition(560,512);
    test2.setPosition(624,512);
    test3.setPosition(688,512);

    sf::Sprite allTilesRevealed[boardWidth][boardHeight];
    sf::Sprite allTilesHidden[boardWidth][boardHeight];
    sf::Sprite allFlags[boardWidth][boardHeight];
    sf::Sprite allMines[boardWidth][boardHeight];
    sf::Sprite allDigits[boardWidth][boardHeight];

    for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardHeight; j++){
            allTilesRevealed[i][j].setTexture(allTextures["tileRevealed"]);
            allTilesHidden[i][j].setTexture(allTextures["tileHidden"]);
            allFlags[i][j].setTexture(allTextures["flag"]);
            allMines[i][j].setTexture(allTextures["mine"]);

            allTilesRevealed[i][j].setPosition(i*tilePixelLength,j*tilePixelLength);
            allTilesHidden[i][j].setPosition(i*tilePixelLength,j*tilePixelLength);
            allFlags[i][j].setPosition(i*tilePixelLength,j*tilePixelLength);
            allMines[i][j].setPosition(i*tilePixelLength,j*tilePixelLength);
            allDigits[i][j].setPosition(i*tilePixelLength,j*tilePixelLength);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (sf::Mouse::getPosition().x < (window.getPosition().x + tilePixelLength * boardWidth) &&
                    sf::Mouse::getPosition().y < (window.getPosition().y + tilePixelLength * boardHeight) &&
                    sf::Mouse::getPosition().x > (window.getPosition().x) &&
                    sf::Mouse::getPosition().y > (window.getPosition().y)) {

                    if(!gameEnded) {

                        int tileIndexX = (sf::Mouse::getPosition().x - window.getPosition().x) / tilePixelLength;
                        int tileIndexY = (sf::Mouse::getPosition().y - window.getPosition().y) / tilePixelLength;

                        mainBoard.tileLeftClick(tileIndexX,tileIndexY);

                        if (mainBoard.getBoardData()[tileIndexX][tileIndexY].clickedBomb()) {
                            mainBoard.getBoardData()[tileIndexX][tileIndexY].revealed = false;
                            gameEnded = true;
                            gameWon = false;
                        }
                    }
                }else if (sf::Mouse::getPosition().x < (window.getPosition().x + 432) &&
                    sf::Mouse::getPosition().y < (window.getPosition().y + 576) &&
                    sf::Mouse::getPosition().x > (window.getPosition().x + 368) &&
                    sf::Mouse::getPosition().y > (window.getPosition().y + 512)) {

                    mainBoard.randomizeBoard();
                    gameEnded = false;
                    gameWon = false;

                }else if(sf::Mouse::getPosition().x < (window.getPosition().x + 560) &&
                        sf::Mouse::getPosition().y < (window.getPosition().y + 576) &&
                        sf::Mouse::getPosition().x > (window.getPosition().x + 496) &&
                        sf::Mouse::getPosition().y > (window.getPosition().y + 512)) {

                    debugMode = !debugMode;
                    gameEnded = false;
                    gameWon = false;

                }else if(sf::Mouse::getPosition().x < (window.getPosition().x + 624) &&
                         sf::Mouse::getPosition().y < (window.getPosition().y + 576) &&
                         sf::Mouse::getPosition().x > (window.getPosition().x + 560) &&
                         sf::Mouse::getPosition().y > (window.getPosition().y + 512)) {

                    mainBoard.importFromFile("boards/testboard1.brd");
                    gameEnded = false;
                    gameWon = false;

                }else if(sf::Mouse::getPosition().x < (window.getPosition().x + 688) &&
                         sf::Mouse::getPosition().y < (window.getPosition().y + 576) &&
                         sf::Mouse::getPosition().x > (window.getPosition().x + 624) &&
                         sf::Mouse::getPosition().y > (window.getPosition().y + 512)) {

                    mainBoard.importFromFile("boards/testboard2.brd");
                    gameEnded = false;
                    gameWon = false;

                }else if(sf::Mouse::getPosition().x < (window.getPosition().x + 752) &&
                         sf::Mouse::getPosition().y < (window.getPosition().y + 576) &&
                         sf::Mouse::getPosition().x > (window.getPosition().x + 688) &&
                         sf::Mouse::getPosition().y > (window.getPosition().y + 512)) {

                    mainBoard.importFromFile("boards/testboard3.brd");
                    gameEnded = false;
                    gameWon = false;

                }
            }else if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && !gameEnded) {
                if (sf::Mouse::getPosition().x < (window.getPosition().x + tilePixelLength * boardWidth) &&
                    sf::Mouse::getPosition().y < (window.getPosition().y + tilePixelLength * boardHeight) &&
                    sf::Mouse::getPosition().x > (window.getPosition().x) &&
                    sf::Mouse::getPosition().y > (window.getPosition().y)) {

                    int tileIndexX = (sf::Mouse::getPosition().x - window.getPosition().x) / tilePixelLength;
                    int tileIndexY = (sf::Mouse::getPosition().y - window.getPosition().y) / tilePixelLength;

                    mainBoard.tileRightClick(tileIndexX,tileIndexY);
                }
            }
        }

        bool allTilesCorrect = true;

        for (int i = 0; i < boardWidth; i++){
            for (int j = 0; j < boardHeight; j++){
                if(!mainBoard.getBoardData()[i][j].correctReveal()){
                    allTilesCorrect = false;
                    goto end_loop;
                }
            }
        }
        end_loop:

        if(allTilesCorrect){
            gameEnded = true;
            gameWon = true;
        }

        window.clear();

        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);

        for (int i = 0; i < boardWidth; i++){
            for (int j = 0; j < boardHeight; j++){

                if(gameEnded){
                    if(gameWon){
                        window.draw(winFace);

                        if(mainBoard.getBoardData()[i][j].revealed){
                            window.draw(allTilesRevealed[i][j]);
                        }else{
                            window.draw(allTilesHidden[i][j]);
                            mainBoard.getBoardData()[i][j].flagged = true;
                            window.draw(allFlags[i][j]);
                        }
                    }else{
                        window.draw(loseFace);
                        if(mainBoard.getBoardData()[i][j].revealed){
                            window.draw((allTilesRevealed[i][j]));

                        }else{
                            if(mainBoard.getBoardData()[i][j].dangerous){
                                window.draw((allTilesRevealed[i][j]));
                                window.draw((allMines[i][j]));
                            }else{
                                window.draw(allTilesHidden[i][j]);
                                if(mainBoard.getBoardData()[i][j].flagged){
                                    window.draw(allFlags[i][j]);
                                }
                            }
                        }
                    }
                }else{

                    window.draw(face);
                    if (mainBoard.getBoardData()[i][j].flagged){
                        window.draw(allTilesHidden[i][j]);
                        window.draw(allFlags[i][j]);
                    }else{
                        if(mainBoard.getBoardData()[i][j].revealed){
                            window.draw(allTilesRevealed[i][j]);
                            window.draw(allDigits[i][j]);
                        }else{
                            window.draw(allTilesHidden[i][j]);
                        }
                    }
                }

                mineStatus = mainBoard.mineCounter() - mainBoard.flagCounter();

                int counter = 0;

                if (mineStatus < 0){
                    counter = 1;
                    window.draw(minus);
                }else{
                    counter = 0;
                }

                int digit;
                for(int i = 100; i > 0; i /= 10){
                    digit = (abs(mineStatus) / i) % 10;
                    digits[digit].setPosition(counter * 21, tilePixelLength * boardHeight);
                    window.draw(digits[digit]);
                    counter++;
                }

                if (debugMode) {
                    if(mainBoard.getBoardData()[i][j].dangerous){
                        window.draw(allMines[i][j]);
                    }
                }

                if (mainBoard.getBoardData()[i][j].revealed){
                    if (mainBoard.getBoardData()[i][j].minesCounter > 0) {
                        allDigits[i][j].setTexture(allTextures[to_string(mainBoard.getBoardData()[i][j].minesCounter)]);
                        window.draw(allDigits[i][j]);
                    }else{
                        allDigits[i][j].setTexture(allTextures["tileRevealed"]);
                    }
                }
            }
        }
        window.display();
    }
    return 0;
}