#pragma once
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include <iostream>

class RunSession {
private:
    ScoringSystem scoring;
    ShopSystem shop;
    int currentRound = 1;
    const int maxRounds = 3;

public:
    void startRun() {
        std::cout << "Starting new run...\n";
        while (currentRound <= maxRounds) {
            playRound();
        }
        std::cout << "Run Ended. Thanks for playing!\n";
    }

private:
    void playRound() {
        std::cout << "\n=== Round " << currentRound << " ===\n";
        int baseScore = 50; // Simulasi hand sederhana
        
        std::cout << "Playing hand... Base score is " << baseScore << "\n";
        int finalScore = scoring.calculate(baseScore);
        std::cout << "Final Score for Round " << currentRound << ": " << finalScore << "\n";

        if (currentRound < maxRounds) {
            shop.visitShop(scoring);
        }
        currentRound++;
    }
};