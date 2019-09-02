#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Board.h"
#include "Block.h"
#include <queue>
using namespace std;

int main()
{
    Board board;
    sf::RenderWindow window(sf::VideoMode(800, 600), "MineSweeper");

    bool debugclicked = false;

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (unsigned i = 0;i < 25; i++) {
                    for (unsigned j = 0;j < 16; j++) {
                        if (board.blocks[i][j]->topSprite.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                            if (board.blocks[i][j]->isFlag == false &&
                            board.gameOver == false && board.win == false) {
                                board.blocks[i][j]->Reveal();
                            }
                            if (board.blocks[i][j]->Mine && !board.blocks[i][j]->isFlag) {
                                board.gameOver = true;
                                board.debugMode = true;
                                board.setDebugMode();
                                board.ButtonTexture();
                            }

                        } else if (board.Debug.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                            if(!debugclicked && !board.debugMode){
                                board.debugMode = true;
                                board.setDebugMode();
                            }

                            else if(!debugclicked && board.debugMode){
                                board.debugMode = false;
                                board.setDebugMode();
                            }


                            debugclicked = true;
                        }
                        else if (board.Test1.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                            if(board.debugMode){
                                board.debugMode = false;
                                board.setDebugMode();
                            }
                            string filename = "boards/testboard1.brd";
                            board.TestBoard(filename);
                            board.gameOver = false;
                            board.win = false;
                            board.ButtonTexture();
                        }
                        else if (board.Test2.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                            if(board.debugMode){
                                board.debugMode = false;
                                board.setDebugMode();
                            }
                            string filename = "boards/testboard2.brd";
                            board.gameOver = false;
                            board.win = false;
                            board.ButtonTexture();
                            board.TestBoard(filename);
                        }
                        else if (board.Test3.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                            if(board.debugMode){
                                board.debugMode = false;
                                board.setDebugMode();
                            }
                            string filename = "boards/testboard3.brd";
                            board.gameOver = false;
                            board.win = false;
                            board.ButtonTexture();
                            board.TestBoard(filename);
                        }

                        else if (board.Restart.getGlobalBounds().contains(
                                (sf::Vector2f) sf::Mouse::getPosition(window))) {
                                if(board.debugMode){
                                    board.debugMode = false;
                                    board.setDebugMode();
                                }
                                board.Reset();
                                board.gameOver = false;
                                board.win = false;
                                board.ButtonTexture();
                        }
                    }

                }

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                for (unsigned i = 0; i < 25; i++) {
                    for (unsigned j = 0; j < 16; j++) {
                        if (board.blocks[i][j]->topSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window))) {
                            if (board.blocks[i][j]->isFlag == false &&
                            board.blocks[i][j]->Revealed == false &&!board.gameOver) {
                                board.blocks[i][j]->Flag();
                                /*if (board.blocks[i][j]->Mine) {
                                    //board.mineCount--;
                                    board.blocks[i][j]->Flag();
                                }*/
                            }
                            else if (board.debugMode && board.blocks[i][j]->Mine) {
                                board.blocks[i][j]->Flag();
                            }
                            else if (board.blocks[i][j]->isFlag){
                                //if it is already a flag, reset it back
                                board.blocks[i][j]->isFlag = false;
                            }

                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased){

                //clickingblock=false;
                debugclicked = false;
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear();

        for (unsigned i = 0; i < 25; i++) {
            for (unsigned j = 0; j < 16; j++) {

                board.blocks[i][j]->SetTexture();
                window.draw(board.blocks[i][j]->bottomSprite);
                if (board.blocks[i][j]->Revealed) {
                    window.draw(board.blocks[i][j]->topSprite);
                }
                if (board.debugMode) {
                    if (board.blocks[i][j]->Mine) {
                        window.draw(board.blocks[i][j]->topSprite);
                    }
                }
                if (board.blocks[i][j]->isFlag) {
                    window.draw(board.blocks[i][j]->flag);
                }



            }
        }
        board.Win();
        if (board.win) {
            for (unsigned i = 0; i < 25; i++) {
                for (unsigned j = 0; j < 16; j++) {
                    if (board.blocks[i][j]->Mine) {
                        board.blocks[i][j]->isFlag = true;
                    }
                }
            }
            board.ButtonTexture();
        }
        window.draw(board.Debug);
        window.draw(board.Restart);
        window.draw(board.Test1);
        window.draw(board.Test2);
        window.draw(board.Test3);

        if (board.FlagCounter() < 0) {
            window.draw(board.countersign);
        }
        board.CounterTexture();
        window.draw(board.counter);
        window.draw(board.counter1);
        window.draw(board.counter2);
        window.display();
    }
    return 0;
}


/*
 *
 * for i
 * for j
 * if (byte = 1)
 * blocks[i][j]->Mine = true;
 * else blocks->Mine = false;
 * ignore the 26th character on each line for test boards
 *
 */