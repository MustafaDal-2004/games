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

class SlotMachine {
private:
    RNG& rng;
    int reels;
    int rows;

    std::vector<std::vector<std::string>> reelStrips;

    std::vector<std::vector<int>> paylines = {
        {1,1,1,1,1}, // middle
        {0,0,0,0,0}, // top
        {2,2,2,2,2}, // bottom
        {0,1,2,1,0}, // V
        {2,1,0,1,2}  // inverted V
    };

    std::unordered_map<std::string, std::vector<int>> paytable = {
        {"Cherry",  {0,0,10,20,50}},
        {"Lemon",   {0,0,5,10,25}},
        {"Bell",    {0,0,20,40,100}},
        {"Star",    {0,0,50,100,250}},
        {"Diamond", {0,0,100,250,500}}
    };

public:
    SlotMachine(RNG& rngRef, int reels = 5, int rows = 3)
        : rng(rngRef), reels(reels), rows(rows)
    {
        // Each reel has its own strip (weighted if you want later)
        reelStrips = {
            {"Cherry","Lemon","Bell","Star","Diamond","Cherry","Lemon"},
            {"Lemon","Cherry","Star","Bell","Diamond","Lemon","Cherry"},
            {"Bell","Star","Cherry","Lemon","Diamond","Bell","Star"},
            {"Star","Bell","Lemon","Cherry","Diamond","Star","Bell"},
            {"Diamond","Cherry","Lemon","Bell","Star","Diamond","Cherry"}
        };
    }

    // Spin → returns 3 rows × 5 reels
    std::vector<std::vector<std::string>> spin() {
        std::vector<std::vector<std::string>> screen(
            rows, std::vector<std::string>(reels)
        );

        for (int r = 0; r < reels; r++) {
            auto& strip = reelStrips[r];
            int stop = rng.uniformInt(0, strip.size() - 1);

            for (int row = 0; row < rows; row++) {
                screen[row][r] =
                    strip[(stop + row) % strip.size()];
            }
        }

        return screen;
    }
    int evaluatePaylines(
        const std::vector<std::vector<std::string>>& screen,
        int betPerLine
    ) {
        int totalPayout = 0;

        for (const auto& line : paylines) {

            // symbol on reel 0 for this payline
            const std::string& base =
                screen[line[0]][0];

            int matches = 1;

            // check reels 1 → 4
            for (int reel = 1; reel < reels; reel++) {
                const std::string& sym =
                    screen[line[reel]][reel];

                if (sym == base)
                    matches++;
                else
                    break;
            }

            // pay only if 3 or more consecutive
            if (matches >= 3) {
                totalPayout +=
                    betPerLine * paytable[base][matches - 1];
            }
        }

        return totalPayout;
    }
};

int main() {
    RNG rng;
    SlotMachine slot(rng);

    int credits = 100;
    int betPerLine = 1;

    while (credits > 0) {
        std::cout << "\nCredits: " << credits << "\n";
        std::cout << "Bet per line (1 credit, 5 lines total = 5 credits)\n";
        std::cout << "Press ENTER to spin, q + ENTER to quit: ";

        std::string input;
        std::getline(std::cin, input);
        if (!input.empty() && input[0] == 'q')
            break;

        int totalBet = betPerLine * 5;
        if (credits < totalBet) {
            std::cout << "Not enough credits!\n";
            break;
        }

        credits -= totalBet;

        // Spin
        auto screen = slot.spin();

        // Display screen
        std::cout << "\n";
        for (const auto& row : screen) {
            for (const auto& sym : row) {
                std::cout << sym << "\t";
            }
            std::cout << "\n";
        }

        // Evaluate paylines
        int payout = slot.evaluatePaylines(screen, betPerLine);
        credits += payout;

        std::cout << "\nPayout: " << payout << "\n";
    }

    std::cout << "\nGame over. Final credits: " << credits << "\n";
    return 0;
}

