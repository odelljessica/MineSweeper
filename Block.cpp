//
// Created by Jessica O'Dell on 2019-04-02.
//

#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

Block::Block(int x, int y) {
    this->x = x;
    this->y = y;
    Mine = false;
    isFlag = false;
    Revealed = false;
    MineTexture.loadFromFile("images/mine.png");
    blockTexture.loadFromFile("images/tile_hidden.png");
    bottomTexture.loadFromFile("images/tile_revealed.png");
    topSprite.setTexture(blockTexture);
    bottomSprite.setTexture(bottomTexture);
    topSprite.setPosition((32 * x), (32 * y));
    flag.setPosition((32 * x), (32 * y));
    bottomSprite.setPosition((32 * x), (32 * y));
    MineTexture.loadFromFile("images/mine.png");
    flagTexture.loadFromFile("images/flag.png");
    bottomTexture.loadFromFile("images/tile_revealed.png");
    bottomTexture.loadFromFile("images/tile_revealed.png");
    oneTexture.loadFromFile("images/number_1.png");
    twoTexture.loadFromFile("images/number_2.png");
    threeTexture.loadFromFile("images/number_3.png");
    fourTexture.loadFromFile("images/number_4.png");
    fiveTexture.loadFromFile("images/number_5.png");
    sixTexture.loadFromFile("images/number_6.png");
    sevenTexture.loadFromFile("images/number_7.png");
    eightTexture.loadFromFile("images/number_8.png");
}

sf::Sprite &Block::getTopSprite() {
    return topSprite;
}

sf::Sprite &Block::getBottomSprite() {
    return bottomSprite;
}

int Block::getValue() {
    return mineNum;
}

void Block::Hide() {
    blockTexture.loadFromFile("images/tile_hidden.png");
    topSprite.setTexture(blockTexture);
}

int Block::MineCount() {
    if (top != nullptr) {
        if (top->Mine) {
            mineNum++;
        }
    }
    if (topRight != nullptr) {
        if (topRight->Mine) {
            mineNum++;
        }
    }
    if (topLeft != nullptr) {
        if (topLeft->Mine) {
            mineNum++;
        }
    }
    if (right != nullptr) {
        if (right->Mine) {
            mineNum++;
        }
    }
    if (left != nullptr) {
        if (left->Mine) {
            mineNum++;
        }
    }
    if (bottom != nullptr) {
        if (bottom->Mine) {
            mineNum++;
        }
    }
    if (bottomRight != nullptr) {
        if (bottomRight->Mine) {
            mineNum++;
        }
    }

    if (bottomLeft != nullptr) {
        if (bottomLeft->Mine) {
            mineNum++;
        }
    }
    if (mineNum > 8) {
        cout << "mine number too high" << endl;
    }
    return mineNum;
}

void Block::Flag() {
    //flagTexture.loadFromFile("images/flag.png");
    //bottomTexture.loadFromFile("images/tile_revealed.png");
    isFlag = true;
    SetTexture();

}

void Block::SetTexture() {

    if (Revealed) {

        if (Mine) {
            topSprite.setTexture(MineTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had a mine" << endl;
        }
        else if (mineNum == 0) {
            topSprite.setTexture(bottomTexture);
            //cout << "this had no mines" << endl;
        }
        else if (mineNum == 1) {
            topSprite.setTexture(oneTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 1 mine" << endl;
        }
        else if (mineNum == 2) {
            topSprite.setTexture(twoTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 2 mines" << endl;

        }
        else if (mineNum == 3) {
            topSprite.setTexture(threeTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 3" << endl;
        }
        else if (mineNum == 4) {
            topSprite.setTexture(fourTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 4 mines"<< endl;
        }
        else if (mineNum == 5) {
            topSprite.setTexture(fiveTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 5 mines" << endl;
        }
        else if (mineNum == 6) {
            topSprite.setTexture(sixTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 6 mines" << endl;
        }
        else if (mineNum == 7) {
            topSprite.setTexture(sevenTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 7 mines" << endl;
        }
        else if (mineNum == 8) {
            topSprite.setTexture(eightTexture);
            bottomSprite.setTexture(bottomTexture);
            //cout << "this had 8 mines" << endl;
        }
    }
    else {
        blockTexture.loadFromFile("images/tile_hidden.png");
        bottomSprite.setTexture(blockTexture);
    }
    if (isFlag) {
        flag.setTexture(flagTexture);
        bottomSprite.setTexture(bottomTexture);
    }

}

void Block::Reveal() {

    cout << x << " and " <<  y << endl;
    Revealed = true;
    SetTexture();
    if (mineNum == 0 && Mine == false) {
        if (top != nullptr && top->Revealed == false) {
            top->Reveal();
        }
        if (topRight != nullptr && topRight->Revealed == false) {
            topRight->Reveal();
        }
        if (topLeft != nullptr && topLeft->Revealed == false) {
            topLeft->Reveal();
        }
        if (left != nullptr && left->Revealed == false) {
            left->Reveal();
        }
        if (right != nullptr && right->Revealed == false) {
            right->Reveal();
        }
        if (bottom != nullptr && bottom->Revealed == false) {
            bottom->Reveal();
        }
        if (bottomRight != nullptr && bottomRight->Revealed == false) {
            bottomRight->Reveal();
        }
        if (bottomLeft != nullptr && bottomLeft->Revealed == false) {
            bottomLeft->Reveal();
        }
    }

};

