#pragma once
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream>

class RunSession {
private:
    ScoringSystem scoring;
    ShopSystem shop;
    Deck deck;
    int currentRound = 1;
    const int maxRounds = 3;

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

        Hand hand;
        drawOpeningHand(hand);

        std::cout << "Hand drawn: " << hand.toString() << "\n";

        int finalScore = scoring.calculateFromHand(hand);
        std::cout << "Final Score for Round " << currentRound
                  << ": " << finalScore << "\n";

        if (currentRound < maxRounds) {
            shop.visitShop(scoring);
        }

        currentRound++;
    }

    void drawOpeningHand(Hand& hand) {
        if (!deck.hasEnoughCards(5)) {
            std::cout << "Deck is low. Regenerating and reshuffling deck...\n";
            deck.generateStandardDeck();
            deck.shuffleDeck();
        }

        hand.clear();
        for (int i = 0; i < 5; ++i) {
            hand.addCard(deck.drawCard());
        }

        std::cout << "Remaining cards in deck: " << deck.remainingCards() << "\n";
    }
};