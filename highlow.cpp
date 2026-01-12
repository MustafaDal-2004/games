#include <iostream>
#include <random>
#include <string>

int randomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min,max);
    return dist(gen);
}

double highlow(int bet, int guess, int randNum) {
    double houseEdge = 0.02;
    if (guess < randNum) {
        double payout = bet * (100.0 / (100.0 - guess)) * (1.0-houseEdge);
        return payout;
    }
    else {
        return 0.0;
    }
}

int main() {
    double balance = 100.0;
    int bet;
    int guess;

    std::cout << "Welcome to High–Low!\n";
    std::cout << "Guess a number (1–99). If the number is higher, you win.\n";

    while (balance > 0) {
        std::cout << "\nBalance: $" << balance << "\n";
        std::cout << "Enter bet (0 to quit): ";
        std::cin >> bet;

        if (bet == 0 || bet > balance) {
            break;
        }

        std::cout << "Enter your guess (1–99): ";
        std::cin >> guess;

        int randNum = randomInt(1, 100);
        double payout = highlow(bet, guess, randNum);

        std::cout << "Random number was: " << randNum << "\n";

        if (payout > 0) {
            std::cout << "You WIN! Payout: $" << payout << "\n";
            balance += payout - bet;
        } else {
            std::cout << "You lose.\n";
            balance -= bet;
        }
    }

    std::cout << "\nGame over. Final balance: $" << balance << "\n";
    return balance;
}
