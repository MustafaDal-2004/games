#include <iostream>
#include <vector>
#include <random>
#include <string>

// SlotMachine class
class SlotMachine {
private:
    std::vector<std::string> symbols; // reel symbols
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    SlotMachine() : symbols({"Cherry", "Lemon", "Orange", "Bell", "Seven"}), dist(0, 4) {
        std::random_device rd;
        gen = std::mt19937(rd());
    }

    // Spin one reel
    std::string spinReel() {
        return symbols[dist(gen)];
    }

    // Spin all 3 reels
    std::vector<std::string> spin() {
        return {spinReel(), spinReel(), spinReel()};
    }

    // Calculate payout based on the spin
    int payout(const std::vector<std::string>& reels, int bet) {
        if (reels[0] == reels[1] && reels[1] == reels[2]) {
            if (reels[0] == "Seven") return bet * 10; // jackpot
            return bet * 5; // three matching symbols
        }
        if (reels[0] == reels[1] || reels[1] == reels[2] || reels[0] == reels[2]) {
            return bet * 2; // two matching symbols
        }
        return 0; // no match
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
        if (bet > balance) {
            std::cout << "Not enough balance!\n";
            continue;
        }

        std::vector<std::string> reels = machine.spin();
        std::cout << "Spinning... \n";
        std::cout << "| " << reels[0] << " | " << reels[1] << " | " << reels[2] << " |\n";

        int win = machine.payout(reels, bet);
        if (win > 0) {
            std::cout << "You won $" << win << "!\n";
            balance += win;
        } else {
            std::cout << "No match. You lose $" << bet << ".\n";
            balance -= bet;
        }

        std::cout << "Current balance: $" << balance << "\n";
    }

    std::cout << "Thanks for playing! Final balance: $" << balance << "\n";
    return 0;
}