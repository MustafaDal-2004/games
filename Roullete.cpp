// ------------------ Roulette Game ------------------
class Roulette : public Game {
public:
    // House edge: typically 5.26% for American Roulette
    double houseEdge;

    Roulette(double edge = 0.0526) : houseEdge(edge) {}

    // Bets: 0 = Red, 1 = Black, 2 = Odd, 3 = Even, 4 = Single Number (1-36)
    enum BetType { RED, BLACK, ODD, EVEN, NUMBER };

    // play a single spin
    double play(double bet, RNG& rng) override {
        int spin = rng.uniformInt(1, 38); // 1-38, where 37 = 0, 38 = 00
        int winningNumber = (spin <= 36) ? spin : 0; // 0 for 37 or 38

        // Pick a random bet type for demo purposes
        BetType betType = static_cast<BetType>(rng.uniformInt(0, 4));
        int chosenNumber = rng.uniformInt(1, 36); // used if BetType::NUMBER

        bool win = false;

        switch (betType) {
            case RED:
                // For simplicity, assume numbers 1,3,5,...,35 are red
                if (winningNumber >= 1 && winningNumber <= 36 && winningNumber % 2 == 1)
                    win = true;
                break;
            case BLACK:
                // Numbers 2,4,6,...,36 are black
                if (winningNumber >= 1 && winningNumber <= 36 && winningNumber % 2 == 0)
                    win = true;
                break;
            case ODD:
                if (winningNumber >= 1 && winningNumber <= 36 && winningNumber % 2 == 1)
                    win = true;
                break;
            case EVEN:
                if (winningNumber >= 1 && winningNumber <= 36 && winningNumber % 2 == 0)
                    win = true;
                break;
            case NUMBER:
                if (winningNumber == chosenNumber)
                    win = true;
                break;
        }

        if (win) {
            // Payout ratios
            double payout = 0.0;
            if (betType == NUMBER) payout = bet * 35.0 * (1 - houseEdge); // single number pays 35:1
            else payout = bet * 2.0 * (1 - houseEdge); // even-money bets pay 1:1
            return payout;
        }
        return 0.0; // loss
    }

    std::string name() const override {
        return "Roulette";
    }
};
