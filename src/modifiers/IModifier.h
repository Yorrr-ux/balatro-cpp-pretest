#pragma once
#include <string>

class IModifier {
public:
    virtual ~IModifier() = default;
    virtual int apply(int currentScore) = 0;
    virtual std::string getName() = 0;
};