#pragma once
#include <string>

enum class Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Card {
private:
    Suit suit;
    Rank rank;

public:
    Card(Suit s, Rank r) : suit(s), rank(r) {}

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }

    std::string toString() const;
};