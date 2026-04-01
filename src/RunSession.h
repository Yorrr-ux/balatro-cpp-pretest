#pragma once
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

        // 🔁 LOOP sampai player memilih PLAY
        while (true) {
            std::cout << "\nYour hand:\n";
            std::cout << playerHand.toIndexedString() << "\n";

            std::cout << "\nChoose action:\n";
            std::cout << "1. Play Hand\n";
            std::cout << "2. Discard Cards\n";
            std::cout << "Choice: ";

            int choice;
            std::cin >> choice;

            if (choice == 1) {
                // PLAY
                Hand playedHand = chooseCardsToPlay(playerHand);

                std::cout << "\nCards played:\n";
                std::cout << playedHand.toString() << "\n";

                int finalScore = scoring.calculateFromHand(playedHand);

                std::cout << "Final Score for Round " << currentRound
                          << ": " << finalScore << "\n";

                break; // keluar loop → round selesai
            }
            else if (choice == 2) {
                // DISCARD
                discardCards(playerHand);

                // ⚠️ tetap di round yang sama
                std::cout << "\nCards discarded. Continuing round...\n";
            }
            else {
                std::cout << "Invalid choice.\n";
            }
        }

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

    // ========================
    // PLAY HAND
    // ========================
    Hand chooseCardsToPlay(Hand& playerHand) {
        while (true) {
            std::cout << "\nChoose cards to play (max 5).\n";
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
                std::cout << "Max 5 cards.\n";
                continue;
            }

            if (!validateIndices(indices, playerHand)) {
                std::cout << "Invalid indices.\n";
                continue;
            }

            Hand playedHand;
            for (int i : indices) {
                playedHand.addCard(playerHand.getCards()[i]);
            }

            return playedHand;
        }
    }

    // ========================
    // DISCARD SYSTEM 🔥
    // ========================
    void discardCards(Hand& playerHand) {
        std::cout << "\nChoose cards to discard.\n";
        std::cout << "Example: 1 3 5\n";
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
            std::cout << "No cards discarded.\n";
            return;
        }

        if (!validateIndices(indices, playerHand)) {
            std::cout << "Invalid discard indices.\n";
            return;
        }

        // 🔥 penting: sort descending biar erase aman
        std::sort(indices.begin(), indices.end(), std::greater<int>());

        for (int i : indices) {
            playerHand.removeCardAt(i);
        }

        // draw kartu baru sesuai jumlah discard
        int drawCount = indices.size();

        if (!deck.hasEnoughCards(drawCount)) {
            deck.generateStandardDeck();
            deck.shuffleDeck();
        }

        for (int i = 0; i < drawCount; ++i) {
            playerHand.addCard(deck.drawCard());
        }
    }

    // ========================
    // VALIDATION HELPER
    // ========================
    bool validateIndices(const std::vector<int>& indices, const Hand& hand) {
        for (size_t i = 0; i < indices.size(); ++i) {
            if (!hand.isValidIndex(indices[i])) {
                return false;
            }

            for (size_t j = i + 1; j < indices.size(); ++j) {
                if (indices[i] == indices[j]) {
                    return false;
                }
            }
        }
        return true;
    }
};