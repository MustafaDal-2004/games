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

// ------------------ Monte Carlo Simulator ------------------
struct SimulationResult {
    double rtp;
    double ev;
    double variance;
    double stddev;
    double hitRate;
};

class Simulator {
public:
    SimulationResult run(Game& game, int trials, double bet) {
        RNG rng;
        double totalReturn = 0.0;
        double totalWager = 0.0;
        double sumSq = 0.0;
        int hits = 0;

        for (int i = 0; i < trials; ++i) {
            double result = game.play(bet, rng);
            totalReturn += result;
            totalWager += bet;
            if (result > bet * 0.0001) hits++; // consider non-zero win a hit
            sumSq += result * result;
        }

        double ev = (totalReturn - totalWager) / totalWager; // expected value %
        double mean = totalReturn / trials;
        double variance = (sumSq / trials) - (mean * mean);
        double stddev = std::sqrt(variance);
        double rtp = totalReturn / totalWager * 100.0;
        double hitRate = static_cast<double>(hits) / trials * 100.0;

        return {rtp, ev, variance, stddev, hitRate};
    }
};

// ------------------ Main ------------------
int main() {
    HighLow game(0.02); // 2% house edge
    Simulator sim;

    int trials = 1000000;
    double bet = 1.0;

    SimulationResult res = sim.run(game, trials, bet);

    std::cout << "Game: " << game.name() << "\n";
    std::cout << "Trials: " << trials << "\n";
    std::cout << "Bet: $" << bet << "\n";
    std::cout << "RTP: " << res.rtp << "%\n";
    std::cout << "EV: " << res.ev * 100 << "%\n";
    std::cout << "Variance: " << res.variance << "\n";
    std::cout << "Std Dev: " << res.stddev << "\n";
    std::cout << "Hit Rate: " << res.hitRate << "%\n";

    return 0;
}