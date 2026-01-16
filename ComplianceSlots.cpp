#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>

class RNG {
    private:
        std::mt19937 gen;
    public: 
        RNG(){
            std::random_device rd;
            gen = std::mt19937(rd());
        }
        
        int uniformInt(int min, int max) {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(gen);
        }

        double uniform() {
            std::uniform_real_distribution<double> dist(0, 1);
            return dist(gen);
        }
};

// SlotMachine class
class SlotMachine {
private:
    RNG& rng; // reference to a single RNG
    int reels;
    std::vector<std::string> symbols;
    std::unordered_map<std::string, int> payouts;

public:
    // Constructor
    SlotMachine(RNG& rngRef, int reels = 3)
        : rng(rngRef), reels(reels)
    {
        // Symbols on reels
        symbols = {"Cherry", "Lemon", "Bell", "Star", "Diamond"};

        // Payout for 3 of the same symbol
        payouts = {
            {"Cherry", 10},
            {"Lemon", 5},
            {"Bell", 20},
            {"Star", 50},
            {"Diamond", 100}
        };
    }

    // Spin once, returns symbols
    std::vector<std::string> spin(int bet, int& payout) {
        int S = symbols.size();
        int totalCombinations = std::pow(S, reels);

        // Single random number for all reels
        int roll = rng.uniformInt(0, totalCombinations - 1);

        std::vector<std::string> result;
        int value = roll;

        // Map number to reels using modulo
        for (int i = 0; i < reels; i++) {
            int index = value % S;
            result.push_back(symbols[index]);
            value /= S;
        }

        // Calculate payout
        if (allEqual(result)) {
            payout = bet * payouts[result[0]];
        } else {
            payout = 0;
        }

        return result;
    }

private:
    // Helper: check if all symbols are the same
    bool allEqual(const std::vector<std::string>& vec) {
        for (size_t i = 1; i < vec.size(); i++) {
            if (vec[i] != vec[0]) return false;
        }
        return true;
    }
};

// Main
int main() {
    RNG rng;                 // single RNG
    SlotMachine machine(rng);

    int bet = 5;             // example bet
    int payout = 0;

    auto result = machine.spin(bet, payout);

    std::cout << "Spin result: ";
    for (const auto& s : result) std::cout << s << " ";
    std::cout << "\n";

    if (payout > 0) {
        std::cout << "You win: " << payout << " coins!\n";
    } else {
        std::cout << "No win. Try again!\n";
    }

    return 0;
}