```cpp
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>

// SlotMachine as a Game subclass
class SlotMachine : public Game {
private:
    std::vector<std::string> symbols;
    std::map<std::string, int> payouts;

public:
    SlotMachine() {
        // Define symbols
        symbols = {"Cherry", "Lemon", "Orange", "Bell", "Seven"};

        // Define paytable (3 of a kind)
        payouts["Cherry"] = 5;
        payouts["Lemon"]  = 5;
        payouts["Orange"] = 5;
        payouts["Bell"]   = 5;
        payouts["Seven"]  = 10; // jackpot
    }

    std::string spinReel(RNG& rng) {
        int idx = rng.uniformInt(0, symbols.size() - 1);
        return symbols[idx];
    }

    double play(double bet, RNG& rng) override {
        // Spin 3 reels
        std::string r1 = spinReel(rng);
        std::string r2 = spinReel(rng);
        std::string r3 = spinReel(rng);

        // Three of a kind
        if (r1 == r2 && r2 == r3) {
            return bet * payouts[r1];
        }

        // Two of a kind (any combination)
        if (r1 == r2 || r2 == r3 || r1 == r3) {
            return bet * 2;
        }

        return 0.0; // no match
    }

    std::string name() const override {
        return "Slot Machine";
    }
};