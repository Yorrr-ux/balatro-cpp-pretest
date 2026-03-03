#pragma once
#include "ModifierFactory.h"
#include "ScoringSystem.h"
#include <iostream>
#include <string>

class ShopSystem {
public:
    void visitShop(ScoringSystem& scoring) {
        std::cout << "\n--- Welcome to the Boost Shop! ---\n";
        std::cout << "Available Boosts: 1. Flat Bonus (+10) | 2. Double Score (x2) | 3. Skip\n";
        std::cout << "Choose an option (1-3): ";
        
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            scoring.addModifier(ModifierFactory::createModifier("Flat"));
            std::cout << "Purchased Flat Bonus!\n";
        } else if (choice == 2) {
            scoring.addModifier(ModifierFactory::createModifier("Double"));
            std::cout << "Purchased Double Score!\n";
        } else {
            std::cout << "Skipped shop.\n";
        }
    }
};