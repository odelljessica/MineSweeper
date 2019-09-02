//
// Created by Jessica O'Dell on 2019-04-03.
//

#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Board {
public:
    Board();
    ~Board();
    Block *blocks[25][16] = {};
    void DrawBoard();
    void setNeighbors();
    void RandomMines();
    void setDebugMode();
    void TestBoard(std::string);
    int MineCounter();
    sf::Sprite Debug;
    sf::Sprite Test1;
    sf::Sprite Test2;
    sf::Sprite Test3;
    sf::Sprite Restart;
    sf::Texture test1texture;
    sf::Texture test2texture;
    sf::Texture test3texture;
    sf::Texture restartTexture;
    sf::Texture debugtexture;
    sf::Texture winTexture;
    sf::Texture loseTexture;
    bool gameOver;
    bool win;
    bool debugMode = false;
    int mineCount = 0;
    sf::Sprite countersign; //the "-" of -150
    sf::Sprite counter; //the "1" of -150
    sf::Sprite counter1; //the "5" of -150
    sf::Sprite counter2; // the "0" of -150
    sf::Texture counterTexture;
    void ButtonTexture();
    int FlagCounter();
    void Reset();
    void CounterTexture();
    void Win();
};

