// ------------------ Slot Machine Game ------------------
class SlotMachine5Reel : public Game {
private:
    std::vector<std::string> symbols = {
        "Cherry", "Lemon", "Orange", "Bell", "Seven"
    };

    std::string spinReel(RNG& rng) {
        return symbols[rng.uniformInt(0, symbols.size() - 1)];
    }

    std::vector<std::string> spin(RNG& rng) {
        return {
            spinReel(rng),
            spinReel(rng),
            spinReel(rng),
            spinReel(rng),
            spinReel(rng)
        };
    }

    std::string mostCommonSymbol(const std::vector<std::string>& reels, int& count) {
        std::unordered_map<std::string, int> freq;
        for (const auto& r : reels)
            freq[r]++;

        count = 0;
        std::string best;

        for (const auto& [sym, c] : freq) {
            if (c > count) {
                count = c;
                best = sym;
            }
        }
        return best;
    }

    void rerollNonMatching(std::vector<std::string>& reels,
                           const std::string& symbol,
                           RNG& rng) {
        for (auto& r : reels) {
            if (r != symbol) {
                r = spinReel(rng);
            }
        }
    }

public:
    double play(double bet, RNG& rng) override {
        auto reels = spin(rng);

        int matchCount;
        std::string symbol = mostCommonSymbol(reels, matchCount);

        // One reroll allowed on 3 or 4 matches
        if (matchCount == 3 || matchCount == 4) {
            rerollNonMatching(reels, symbol, rng);
            symbol = mostCommonSymbol(reels, matchCount);
        }

        // Payouts (total return)
        if (matchCount == 5) {
            if (symbol == "Seven")
                return bet * 500.0; // jackpot
            return bet * 100.0;
        }

        return 0.0;
    }

    std::string name() const override {
        return "5-Reel Reroll Slot";
    }
};