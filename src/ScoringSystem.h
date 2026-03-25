#pragma once
#include "modifiers/IModifier.h"
#include "Hand.h"
#include <vector>
#include <memory>
#include <iostream>

class ScoringSystem {
private:
    std::vector<std::unique_ptr<IModifier>> activeModifiers;

public:
    void addModifier(std::unique_ptr<IModifier> mod) {
        if (mod != nullptr) {
            activeModifiers.push_back(std::move(mod));
        }
    }

    int calculate(int baseScore) {
        int finalScore = baseScore;
        std::cout << "Base Score: " << baseScore << "\n";

        for (const auto& mod : activeModifiers) {
            finalScore = mod->apply(finalScore);
            std::cout << "Applied " << mod->getName()
                      << " -> New Score: " << finalScore << "\n";
        }

        return finalScore;
    }

    int calculateFromHand(const Hand& hand) {
        int baseScore = static_cast<int>(hand.getCards().size()) * 10;
        return calculate(baseScore);
    }
};