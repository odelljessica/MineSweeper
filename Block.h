//
// Created by Jessica O'Dell on 2019-04-02.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Block {
public:
    int x = 0;
    int y = 0;
    Block(int, int);
    Block *top = nullptr;
    Block *topRight = nullptr;
    Block *topLeft = nullptr;
    Block *right = nullptr;
    Block *left = nullptr;
    Block *bottom = nullptr;
    Block *bottomLeft = nullptr;
    Block *bottomRight = nullptr;
    void Reveal();
    void SetTexture();
    void RevealAll();
    void setLocation(float, float);
    sf::Sprite &getTopSprite();
    sf::Sprite &getBottomSprite();
    int getValue();
    void Flag();
    void Hide();
    int MineCount();

    sf::Sprite topSprite;
    sf::Texture bottomTexture;
    sf::Texture flagTexture;
    sf::Texture MineTexture;
    sf::Texture blockTexture;
    sf::Texture oneTexture;
    sf::Texture twoTexture;
    sf::Texture threeTexture;
    sf::Texture fourTexture;
    sf::Texture fiveTexture;
    sf::Texture sixTexture;
    sf::Texture sevenTexture;
    sf::Texture eightTexture;
    sf::Sprite bottomSprite;
    sf::Vector2f location;
    sf::Sprite flag;
    bool Mine;
    bool isFlag;
    bool Revealed;
    int mineNum = 0;





};


