#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <memory>

// ------------------ RNG Wrapper ------------------
class RNG {
private:
    std::mt19937 gen;
public:
    RNG() {
        std::random_device rd;
        gen = std::mt19937(rd());
    }

    int uniformInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

    double uniform() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(gen);
    }

    double exponential(double lambda) {
        std::exponential_distribution<double> dist(lambda);
        return dist(gen);
    }
};

// ------------------ Game Interface ------------------
class Game {
public:
    virtual double play(double bet, RNG& rng) = 0; // return winnings
    virtual std::string name() const = 0;
    virtual ~Game() = default;
};

// ------------------ High-Low Example ------------------
class HighLow : public Game {
public:
    double houseEdge;
    HighLow(double edge = 0.02) : houseEdge(edge) {}

    double play(double bet, RNG& rng) override {
        int guess = rng.uniformInt(1, 99);
        int randNum = rng.uniformInt(1, 100);
        if (guess < randNum) {
            return bet * (100.0 / (100 - guess)) * (1 - houseEdge); // total return
        }
        return 0.0;
    }

    std::string name() const override {
        return "High-Low";
    }
};

// ------------------ Simulation Result ------------------
struct SimulationResult {
    double rtp;
    double ev;
    double variance;
    double stddev;
    double hitRate;
    double totalProfit; // profit for casino
};

// ------------------ Simulator ------------------
class Simulator {
public:
    SimulationResult run(Game& game, int trials, double lambda, double minBet, double maxBet) {
        RNG rng;
        double totalReturn = 0.0;
        double totalWager = 0.0;
        double sumSq = 0.0;
        int hits = 0;

        for (int i = 0; i < trials; ++i) {
            // Draw bet from exponential distribution
            double bet = rng.exponential(lambda);
            if (bet < minBet) bet = minBet;
            if (bet > maxBet) bet = maxBet;

            double result = game.play(bet, rng);
            totalReturn += result;
            totalWager += bet;
            if (result > bet * 0.0001) hits++; // non-zero win
            sumSq += result * result;
        }

        double mean = totalReturn / trials;
        double variance = (sumSq / trials) - (mean * mean);
        double stddev = std::sqrt(variance);
        double rtp = totalReturn / totalWager * 100.0;
        double ev = (totalReturn - totalWager) / totalWager;
        double hitRate = static_cast<double>(hits) / trials * 100.0;
        double totalProfit = totalWager - totalReturn; // casino profit

        return {rtp, ev, variance, stddev, hitRate, totalProfit};
    }
};

// ------------------ Main ------------------
int main() {
    HighLow game(0.02); // Example game
    Simulator sim;

    int trials = 100000;
    double lambda = 0.01; // controls average bet size
    double minBet = 0.0;
    double maxBet = 500.0;

    SimulationResult result = sim.run(game, trials, lambda, minBet, maxBet);

    std::cout << "Game: " << game.name() << "\n";
    std::cout << "Trials: " << trials << "\n";
    std::cout << "RTP: " << result.rtp << "%\n";
    std::cout << "EV: " << result.ev << "\n";
    std::cout << "Variance: " << result.variance << "\n";
    std::cout << "StdDev: " << result.stddev << "\n";
    std::cout << "Hit Rate: " << result.hitRate << "%\n";
    std::cout << "Casino Total Profit: $" << result.totalProfit << "\n";

    return 0;
}
