#include "Hand.h"
#include <sstream>
#include <stdexcept>

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

void Hand::clear() {
    cards.clear();
}

const std::vector<Card>& Hand::getCards() const {
    return cards;
}

int Hand::size() const {
    return static_cast<int>(cards.size());
}

bool Hand::isValidIndex(int index) const {
    return index >= 0 && index < static_cast<int>(cards.size());
}

Card Hand::removeCardAt(int index) {
    if (!isValidIndex(index)) {
        throw std::out_of_range("Invalid card index");
    }

    Card selected = cards[index];
    cards.erase(cards.begin() + index);
    return selected;
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

std::string Hand::toIndexedString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < cards.size(); ++i) {
        oss << "[" << i << "] " << cards[i].toString();
        if (i < cards.size() - 1) {
            oss << "\n";
        }
    }
    return oss.str();
}