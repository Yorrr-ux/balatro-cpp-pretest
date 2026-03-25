#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Hand {
private:
    std::vector<Card> cards;

public:
    void addCard(const Card& card);
    void clear();
    const std::vector<Card>& getCards() const;
    std::string toString() const;
};