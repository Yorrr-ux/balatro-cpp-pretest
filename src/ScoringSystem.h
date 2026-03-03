#pragma once
#include "modifiers/IModifier.h"
#include <vector>
#include <memory>
#include <iostream>

class ScoringSystem {
private:
    std::vector<std::unique_ptr<IModifier>> activeModifiers;
public:
    void addModifier(std::unique_ptr<IModifier> mod) {
        activeModifiers.push_back(std::move(mod));
    }

    // Menerapkan Structural Pattern: Decorator-like chain
    int calculate(int baseScore) {
        int finalScore = baseScore;
        std::cout << "Base Score: " << baseScore << "\n";
        for (const auto& mod : activeModifiers) {
            finalScore = mod->apply(finalScore);
            std::cout << "Applied " << mod->getName() << " -> New Score: " << finalScore << "\n";
        }
        return finalScore;
    }
};