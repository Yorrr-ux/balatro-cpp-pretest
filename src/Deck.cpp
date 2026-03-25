#include "Deck.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck() : currentIndex(0) {
    generateStandardDeck();
    shuffleDeck();
}

void Deck::generateStandardDeck() {
    cards.clear();
    currentIndex = 0;

    Suit suits[] = {
        Suit::Hearts,
        Suit::Diamonds,
        Suit::Clubs,
        Suit::Spades
    };

    Rank ranks[] = {
        Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six,
        Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten,
        Rank::Jack, Rank::Queen, Rank::King, Rank::Ace
    };

    for (Suit suit : suits) {
        for (Rank rank : ranks) {
            cards.emplace_back(suit, rank);
        }
    }
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
    currentIndex = 0;
}

Card Deck::drawCard() {
    if (currentIndex >= static_cast<int>(cards.size())) {
        throw std::out_of_range("Deck is empty");
    }
    return cards[currentIndex++];
}

bool Deck::hasEnoughCards(int amount) const {
    return currentIndex + amount <= static_cast<int>(cards.size());
}

int Deck::remainingCards() const {
    return static_cast<int>(cards.size()) - currentIndex;
}