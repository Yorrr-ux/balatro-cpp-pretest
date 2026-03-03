#pragma once
#include "IModifier.h"

class DoubleScoreModifier : public IModifier {
public:
    int apply(int currentScore) override {
        return currentScore * 2;
    }
    std::string getName() override {
        return "Double Score (x2)";
    }
};