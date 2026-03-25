#pragma once
#include "IModifier.h"
#include <string>

class FlatBonusModifier : public IModifier {
private:
    int bonus;

public:
    FlatBonusModifier(int b) : bonus(b) {}

    int apply(int currentScore) override {
        return currentScore + bonus;
    }

    std::string getName() override {
        return "Flat Bonus (+" + std::to_string(bonus) + ")";
    }
};