#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>

// SlotMachine class
class SlotMachine {
private:
    std::vector<std::string> symbols; // reel symbols
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    SlotMachine()
        :symbols({"Cherry", "Lemon", "Orange", "Bell", "Seven"}),
        gen(std::random_device{}()),
        dist(0, symbols.size() - 1) {}
        
    // Spin one reel
    std::string spinReel() {
        return symbols[dist(gen)];
    }

    // Spin all 3 reels
    std::vector<std::string> spin() {
        return {spinReel(), spinReel(), spinReel(), spinReel(), spinReel()};
    }

    std::string mostCommonSymbol(const std::vector<std::string>& reels, int& count) {
        std::unordered_map<std::string, int> freq;

        for (const auto& r : reels)
            freq[r]++;

        std::string best;
        count = 0;

        for (const auto& [symbol, c] : freq) {
            if (c > count) {
                count = c;
                best = symbol;
            }
        }

        return best;
    }
    void rerollNonMatching(std::vector<std::string>& reels, const std::string& symbol) {
        for (auto& r : reels) {
            if (r != symbol) {
                r = spinReel();
            }
        }
    }
    
    
    int payout(std::vector<std::string>& reels, int bet) {
        int matchCount;
        std::string symbol = mostCommonSymbol(reels, matchCount);

        // Allow ONE reroll if 3 or 4 match
        if (matchCount == 3 || matchCount == 4) {
            rerollNonMatching(reels, symbol);

            // Recheck after reroll
            symbol = mostCommonSymbol(reels, matchCount);
        }

        // Only pay if all 5 match
        if (matchCount == 5) {
            if (symbol == "Seven")
                return bet * 500;   // 5 Seven jackpot
            return bet * 100;       // 5 of any symbol
        }

        return 0;
    }
};

int main() {
    SlotMachine machine;
    int balance = 100;
    int bet;

    std::cout << "Welcome to C++ Slot Machine!\n";
    std::cout << "You start with $" << balance << "\n";

    while (balance > 0) {
        std::cout << "\nEnter your bet (0 to quit): ";
        std::cin >> bet;

        if (bet == 0) break;

        if (bet < 0 || bet > balance) {
            std::cout << "Invalid bet!\n";
            continue;
        }

        // Spin
        std::vector<std::string> reels = machine.spin();

        std::cout << "\nSpinning...\n| ";
        for (const auto& r : reels)
            std::cout << r << " | ";
        std::cout << "\n";

        // Deduct bet first
        balance -= bet;

        // Payout (may modify reels due to reroll)
        int win = machine.payout(reels, bet);

        // Show reroll result if reels changed
        std::cout << "Final result:\n| ";
        for (const auto& r : reels)
            std::cout << r << " | ";
        std::cout << "\n";

        if (win > 0) {
            std::cout << "You won $" << win << "!\n";
            balance += win;
        } else {
            std::cout << "No win this time.\n";
        }

        std::cout << "Current balance: $" << balance << "\n";
    }

    std::cout << "\nThanks for playing! Final balance: $" << balance << "\n";
    return 0;
}