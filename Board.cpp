//
// Created by Jessica O'Dell on 2019-04-03.
//
#include "Board.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;


void Board::setNeighbors() {
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {

            if (j != 0) {
                if (i == 0) {
                    blocks[i][j]->topLeft = nullptr;
                    blocks[i][j]->top = blocks[i][j - 1]; // just changed from nullptr
                    blocks[i][j]->left = nullptr;
                    blocks[i][j]->bottomLeft = nullptr;
                    blocks[i][j]->topRight = blocks[i + 1][j - 1];
                } else {
                    blocks[i][j]->top = blocks[i][j - 1];
                    blocks[i][j]->left = blocks[i - 1][j];
                    blocks[i][j]->right = blocks[i + 1][j];
                    blocks[i][j]->topLeft = blocks[i - 1][j - 1];
                    blocks[i][j]->topRight = blocks[i + 1][j - 1];
                }
            } else {
                blocks[i][0]->top = nullptr;
                blocks[i][0]->topLeft = nullptr;
                blocks[i][0]->topRight = nullptr;
            }
            if (i != 0) {
                if (j == 0) {
                    if (i == 24) {
                        blocks[i][j]->left = blocks[i - 1][j];
                        blocks[i][j]->topLeft = nullptr;
                        blocks[i][j]->bottomLeft = blocks[i - 1][j + 1];
                    } else {
                        blocks[i][j]->topLeft = nullptr;
                        blocks[i][j]->left = blocks[i - 1][j]; // test from null
                        blocks[i][j]->bottomLeft = blocks[i - 1][j + 1]; // test from null
                    }

                } else {
                    blocks[i][j]->left = blocks[i - 1][j];
                    blocks[i][j]->topLeft = blocks[i - 1][j - 1];
                    blocks[i][j]->bottomLeft = blocks[i - 1][j + 1];
                }
            } else {
                blocks[i][j]->left = nullptr;
                blocks[i][j]->topLeft = nullptr;
                blocks[i][j]->bottomLeft = nullptr;
            }
            if (j != 15) {
                if (i == 0) {
                    blocks[i][j]->bottomLeft = nullptr;
                    blocks[i][j]->bottom = blocks[i][j + 1];
                    blocks[i][j]->bottomRight = blocks[i + 1][j + 1];
                } else if (i == 24) {
                    blocks[i][j]->bottomLeft = blocks[i - 1][j + 1];
                    blocks[i][j]->bottom = blocks[i][j + 1];
                    blocks[i][j]->bottomRight = nullptr;
                } else {
                    blocks[i][j]->bottom = blocks[i][j + 1];
                    blocks[i][j]->bottomLeft = blocks[i - 1][j + 1];
                    blocks[i][j]->bottomRight = blocks[i + 1][j + 1];
                }
            } else {
                blocks[i][15]->bottom = nullptr;
                blocks[i][15]->bottomLeft = nullptr;
                blocks[i][15]->bottomRight = nullptr;
            }

            if (i != 24) {
                if (j == 0) {
                    blocks[i][j]->topRight = nullptr;
                    blocks[i][j]->right = blocks[i + 1][j];
                } else {
                    blocks[i][j]->right = blocks[i + 1][j];
                    blocks[i][j]->topRight = blocks[i + 1][j - 1];
                }
            } else {
                blocks[24][j]->right = nullptr;
                blocks[24][j]->topRight = nullptr;
            }
            //blocks[i][j]->mineNum = blocks[i][j]->MineCount();
        }
    }
}

void Board::setDebugMode() {
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            if (blocks[i][j]->Mine && debugMode) {
                blocks[i][j]->Revealed = true;
            }
            else if (blocks[i][j]->Mine && !debugMode) {
                blocks[i][j]->Revealed = false;
                debugMode = false;
            }
        }
    }

}

int Board::MineCounter() {
    mineCount = 0;
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            if (blocks[i][j]->Mine) {
                mineCount++;
            }
        }
    }
    return mineCount;
}

int Board::FlagCounter() {
    mineCount = MineCounter();
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            if (blocks[i][j]->isFlag) {
                mineCount--;
            }
        }
    }
    return mineCount;
}

void Board::TestBoard(string filename) {

    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j]->mineNum = 0;
            blocks[i][j]->Mine = false;
            blocks[i][j]->isFlag = false;
            blocks[i][j]->Revealed = false;
        }
    }

    ifstream file(filename);
    if (file.is_open()) {
        char value;
        int counter = 0;
        for (int j = 0; j < 16; j++) {
            for (int i = 0; i < 25; i++) {
                if (counter != 25) {
                    file.get(value);
                        counter++;
                        if (value == '1') {
                            blocks[i][j]->Mine = true;
                        } else blocks[i][j]->Mine = false;
                    }
                else {
                    file.get(value);
                    file.get(value);
                    i--;
                    counter = 0;
                }
            }
        }
    }
    setNeighbors();
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j]->mineNum = blocks[i][j]->MineCount();
        }
    }
}

void Board::ButtonTexture() {
    if (gameOver && !win) {
        loseTexture.loadFromFile("images/face_lose.png");
        Restart.setTexture(loseTexture);
    }
    else if (win) {
        winTexture.loadFromFile("images/face_win.png");
        Restart.setTexture(winTexture);
    }
    else {
        restartTexture.loadFromFile("images/face_happy.png");
        Restart.setTexture(restartTexture);
    }
}

void Board::DrawBoard() {

    //set all the buttons
    debugtexture.loadFromFile("images/debug.png");
    Debug.setTexture(debugtexture);
    Debug.setPosition(415,520);

    restartTexture.loadFromFile("images/face_happy.png");
    Restart.setTexture(restartTexture);
    Restart.setPosition(315, 520);

    test1texture.loadFromFile("images/test_1.png");
    Test1.setTexture(test1texture);
    Test1.setPosition(500, 520);

    test2texture.loadFromFile("images/test_2.png");
    Test2.setTexture(test2texture);
    Test2.setPosition(570, 520);

    test3texture.loadFromFile("images/test_3.png");
    Test3.setTexture(test3texture);
    Test3.setPosition(640, 520);

    counterTexture.loadFromFile("images/digits.png");
    countersign.setTexture(counterTexture);
    countersign.setPosition(20, 520);

    counter.setTexture(counterTexture);
    counter.setPosition(20, 520);

    counter1.setTexture(counterTexture);
    counter1.setPosition(40, 520);

    counter2.setTexture(counterTexture);
    counter2.setPosition(60, 520);

    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j] = new Block(i, j);
            //blocks[i][j]->topSprite.setTexture(blockTexture);
            //blocks[i][j]->topSprite.setPosition((32 * i), (32 * j));
            //blocks[i][j]->bottomSprite.setPosition((32 * i), (32 * j));

        }
    }

}
void Board::RandomMines() {
    srand(time(0));
    sf::Texture mineTexture;
    mineTexture.loadFromFile("images/mine.png");
    //int counter = 0;
    for (unsigned i = 0; i < 50; i++) {
        int x = rand() % 25;
        int y = rand() % 16;
        if (blocks[x][y]->Mine) {
            i--;
        }
        else {
            blocks[x][y]->Mine = true;
        }
    }
}

Board::Board() {
    DrawBoard();
    RandomMines();
    setNeighbors();
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j]->mineNum = blocks[i][j]->MineCount();

        }
    }
}

void Board::Reset() {

    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j]->mineNum = 0;
            blocks[i][j]->Mine = false;
            blocks[i][j]->isFlag = false;
            blocks[i][j]->Revealed = false;
        }
    }
    //DrawBoard();
    RandomMines();
    setNeighbors();
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            blocks[i][j]->mineNum = blocks[i][j]->MineCount();
        }
    }
}

void Board::Win() {
    //needs to be fixed
    int revealedNum = 0;
    mineCount = MineCounter();
    //cout << "mine count is " << mineCount << endl;
    int minez = mineCount;
    //cout << "Minecount: " << mineCount << endl;
    win = false;
    for (unsigned i = 0; i < 25; i++) {
        for (unsigned j = 0; j < 16; j++) {
            if (blocks[i][j]->Revealed && !blocks[i][j]->Mine) {
                revealedNum++;

            }
        }
    }
    if (400 - revealedNum == minez) {
        win = true;
    }
    else win = false;

}

void Board::CounterTexture() {
    int counterNum = FlagCounter();
    countersign.setTextureRect(sf::IntRect(0, 0, 21, 32));
    int flagNum = abs(FlagCounter()); // not actual number of flags lol
    int flagz = FlagCounter();
    int ones = flagNum % 10;
    int tenth = flagNum / 10;
    int a = 0, b = 105, c = 0;
    if (ones == 0) {
        a = 0;
    }
    else if (ones == 1) {
        a = 21;
    }
    else if (ones == 2) {
        a = 42;
    }
    else if (ones == 3) {
        a = 63;
    }
    else if (ones == 4) {
        a = 84;
    }
    else if (ones == 5) {
        a = 105;
    }
    else if (ones == 6) {
        a = 126;
    }
    else if (ones == 7) {
        a = 147;
    }
    else if (ones == 8) {
        a = 168;
    }
    else if (ones == 9) {
        a = 189;
    }

    //tenths

    if (tenth == 0) {
        b = 0;
    }
    else if (tenth == 1) {
        b = 21;
    }
    else if (tenth == 2) {
        b = 42;
    }
    else if (tenth == 3) {
        b = 63;
    }
    else if (tenth == 4) {
        b = 84;
    }
    else if (tenth == 5) {
        b = 105;
    }
    else if (tenth == 6) {
        b = 126;
    }
    else if (tenth == 7) {
        b = 147;
    }
    else if (tenth == 8) {
        b = 168;
    }
    else if (tenth == 9) {
        b = 189;
    }
    if (flagz < 0) {
        c = 210;
    }
    int start = MineCounter();
    counter.setTextureRect(sf::IntRect(c,0,21,32));
    counter1.setTextureRect(sf::IntRect(b,0,21,32));
    counter2.setTextureRect(sf::IntRect(a,0,21,32));


}

Board::~Board() {
    for (unsigned i = 0; i < 25; i++){
        for (unsigned j = 0; j < 16; j++) {
            delete blocks[i][j];
        }
    }
}
