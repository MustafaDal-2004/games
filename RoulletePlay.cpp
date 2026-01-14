#include <iostream>
#include <random>
#include <string>

class RouletteGame {
private:
    std::mt19937 gen;

    int spinWheel() {
        std::uniform_int_distribution<int> dist(0, 37); // 0–36, 37 = 00
        return dist(gen);
    }

public:
    RouletteGame() : gen(std::random_device{}()) {}

    void play() {
        int balance = 100;
        int bet;

        std::cout << "🎰 Welcome to Roulette!\n";
        std::cout << "Starting balance: $" << balance << "\n";

        while (balance > 0) {
            std::cout << "\nEnter bet amount (0 to quit): ";
            std::cin >> bet;

            if (bet == 0) break;
            if (bet < 0 || bet > balance) {
                std::cout << "Invalid bet.\n";
                continue;
            }

            std::cout << "\nChoose bet type:\n";
            std::cout << "1) Red\n";
            std::cout << "2) Black\n";
            std::cout << "3) Odd\n";
            std::cout << "4) Even\n";
            std::cout << "5) Single Number (1–36)\n";
            std::cout << "Please Select 1-5\n";
            std::cout << "Selection: ";

            int choice;
            std::cin >> choice;

            int chosenNumber = -1;
            if (choice == 5) {
                std::cout << "Pick a number (1–36): ";
                std::cin >> chosenNumber;
                if (chosenNumber < 1 || chosenNumber > 36) {
                    std::cout << "Invalid number.\n";
                    continue;
                }
            }

            balance -= bet;

            int result = spinWheel();
            std::string resultStr;

            if (result == 37)
                resultStr = "00";
            else
                resultStr = std::to_string(result);

            std::cout << "\n🎡 Spinning... Result: " << resultStr << "\n";

            bool win = false;

            if (result >= 1 && result <= 36) {
                switch (choice) {
                    case 1: win = (result % 2 == 1); break; // Red
                    case 2: win = (result % 2 == 0); break; // Black
                    case 3: win = (result % 2 == 1); break; // Odd
                    case 4: win = (result % 2 == 0); break; // Even
                    case 5: win = (result == chosenNumber); break;
                }
            }

            if (win) {
                int payout = (choice == 5) ? bet * 36 : bet * 2;
                std::cout << "🎉 You win $" << payout << "!\n";
                balance += payout;
            } else {
                std::cout << "❌ You lose.\n";
            }

            std::cout << "Balance: $" << balance << "\n";
        }

        std::cout << "\nThanks for playing! Final balance: $" << balance << "\n";
    }
};

int main() {
    RouletteGame game;
    game.play();
    return 0;
}
