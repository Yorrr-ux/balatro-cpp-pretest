#pragma once
#include "modifiers/IModifier.h"
#include "Hand.h"
#include <vector>
#include <memory>
#include <iostream>

class ScoringSystem {
private:
    std::vector<std::unique_ptr<IModifier>> activeModifiers;

    int getCardValue(const Card& card) {
        Rank rank = card.getRank();

        switch (rank) {
            case Rank::Jack:
            case Rank::Queen:
            case Rank::King:
                return 10;
            case Rank::Ace:
                return 11;
            default:
                return static_cast<int>(rank);
        }
    }

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
        int baseScore = 0;

        std::cout << "Played cards:\n";
        for (const auto& card : hand.getCards()) {
            int value = getCardValue(card);
            std::cout << "- " << card.toString() << " = " << value << "\n";
            baseScore += value;
        }

        return calculate(baseScore);
    }
};