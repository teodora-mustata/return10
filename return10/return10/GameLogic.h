#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"

class GameLogic {
public:
    void gameStart();

private:
    Map map{ 10,10 };
    int score = 0;
    std::chrono::steady_clock::time_point startTime;
    bool gameRunning = true;


    void placePlayer();

    void initializeScores();

    void startTimer();

    void showStartMenu();

    //void gameLoop() {
    //    while (gameRunning) {
    //        std::this_thread::sleep_for(std::chrono::seconds(1));
    //        std::cout << "Game is running..." << std::endl;

    //        if (score >= 100) {
    //            gameRunning = false;
    //            std::cout << "Game Over! You won!" << std::endl;
    //        }
    //    }
    //}
};


