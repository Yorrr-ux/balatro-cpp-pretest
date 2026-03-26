#pragma once
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream>
#include <sstream>
#include <vector>

class RunSession {
private:
    ScoringSystem scoring;
    ShopSystem shop;
    Deck deck;
    int currentRound = 1;
    const int maxRounds = 3;
    const int handSize = 8;
    const int maxPlayedCards = 5;

public:
    void startRun() {
        std::cout << "Starting new run...\n";
        std::cout << "Deck generated with " << deck.remainingCards() << " cards.\n";

        while (currentRound <= maxRounds) {
            playRound();
        }

        std::cout << "Run Ended. Thanks for playing!\n";
    }

private:
    void playRound() {
        std::cout << "\n=== Round " << currentRound << " ===\n";

        Hand playerHand;
        drawPlayerHand(playerHand);

        std::cout << "Your hand:\n";
        std::cout << playerHand.toIndexedString() << "\n";

        Hand playedHand = chooseCardsToPlay(playerHand);

        std::cout << "\nCards played:\n";
        std::cout << playedHand.toString() << "\n";

        int finalScore = scoring.calculateFromHand(playedHand);
        std::cout << "Final Score for Round " << currentRound
                  << ": " << finalScore << "\n";

        if (currentRound < maxRounds) {
            shop.visitShop(scoring);
        }

        currentRound++;
    }

    void drawPlayerHand(Hand& hand) {
        if (!deck.hasEnoughCards(handSize)) {
            std::cout << "Deck is low. Regenerating and reshuffling deck...\n";
            deck.generateStandardDeck();
            deck.shuffleDeck();
        }

        hand.clear();
        for (int i = 0; i < handSize; ++i) {
            hand.addCard(deck.drawCard());
        }

        std::cout << "Remaining cards in deck: " << deck.remainingCards() << "\n";
    }

    Hand chooseCardsToPlay(Hand& playerHand) {
        while (true) {
            std::cout << "\nChoose cards to play.\n";
            std::cout << "Enter up to 5 indexes separated by spaces.\n";
            std::cout << "Example: 0 2 4\n";
            std::cout << "Input: ";

            std::string line;
            std::getline(std::cin >> std::ws, line);

            std::stringstream ss(line);
            std::vector<int> indices;
            int idx;

            while (ss >> idx) {
                indices.push_back(idx);
            }

            if (indices.empty()) {
                std::cout << "You must choose at least 1 card.\n";
                continue;
            }

            if (indices.size() > static_cast<size_t>(maxPlayedCards)) {
                std::cout << "You can only play up to 5 cards.\n";
                continue;
            }

            bool valid = true;

            for (size_t i = 0; i < indices.size(); ++i) {
                if (!playerHand.isValidIndex(indices[i])) {
                    valid = false;
                    break;
                }

                for (size_t j = i + 1; j < indices.size(); ++j) {
                    if (indices[i] == indices[j]) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) {
                    break;
                }
            }

            if (!valid) {
                std::cout << "Invalid input. Make sure indexes exist and are not duplicated.\n";
                continue;
            }

            Hand playedHand;

            for (int selectedIndex : indices) {
                playedHand.addCard(playerHand.getCards()[selectedIndex]);
            }

            return playedHand;
        }
    }
};