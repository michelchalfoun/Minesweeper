#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

void setTextures(map<string, sf::Texture> &textureMap) {

    sf::Texture tempTexture;

    tempTexture.loadFromFile("images/tile_hidden.png");
    textureMap["tileHidden"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/tile_revealed.png");
    textureMap["tileRevealed"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/mine.png");
    textureMap["mine"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/flag.png");
    textureMap["flag"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/face_happy.png");
    textureMap["faceHappy"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/face_lose.png");
    textureMap["faceLose"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/face_win.png");
    textureMap["faceWin"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/debug.png");
    textureMap["debug"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/digits.png");
    textureMap["digits"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_1.png");
    textureMap["1"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_2.png");
    textureMap["2"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_3.png");
    textureMap["3"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_4.png");
    textureMap["4"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_5.png");
    textureMap["5"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_6.png");
    textureMap["6"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_7.png");
    textureMap["7"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/number_8.png");
    textureMap["8"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/test_1.png");
    textureMap["test1"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/test_2.png");
    textureMap["test2"] = sf::Texture(tempTexture);

    tempTexture.loadFromFile("images/test_3.png");
    textureMap["test3"] = sf::Texture(tempTexture);

    for(int i = 0; i < 10; i++) {
        tempTexture.loadFromFile("images/digits.png", sf::IntRect(21 * i, 0, 21, 32));
        textureMap["digit" + to_string(i)] = sf::Texture(tempTexture);
    }

    tempTexture.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
    textureMap["minus"] = sf::Texture(tempTexture);

}
