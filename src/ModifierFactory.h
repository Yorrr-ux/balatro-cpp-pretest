#pragma once
#include "modifiers/IModifier.h"
#include "modifiers/FlatBonusModifier.h"
#include "modifiers/DoubleScoreModifier.h"
#include <memory>
#include <string>

class ModifierFactory {
public:
    static std::unique_ptr<IModifier> createModifier(const std::string& type) {
        if (type == "Flat") {
            return std::make_unique<FlatBonusModifier>(10);
        }
        if (type == "Double") {
            return std::make_unique<DoubleScoreModifier>();
        }
        return nullptr;
    }
};