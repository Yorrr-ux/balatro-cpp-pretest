#include "Hand.h"

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

void Hand::clear() {
    cards.clear();
}

const std::vector<Card>& Hand::getCards() const {
    return cards;
}

std::string Hand::toString() const {
    std::string result;
    for (size_t i = 0; i < cards.size(); ++i) {
        result += cards[i].toString();
        if (i < cards.size() - 1) {
            result += ", ";
        }
    }
    return result;
}