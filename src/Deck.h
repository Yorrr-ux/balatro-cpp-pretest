#pragma once
#include "Card.h"
#include <vector>

class Deck {
private:
    std::vector<Card> cards;
    int currentIndex;

public:
    Deck();

    void generateStandardDeck();
    void shuffleDeck();
    Card drawCard();
    bool hasEnoughCards(int amount) const;
    int remainingCards() const;
};