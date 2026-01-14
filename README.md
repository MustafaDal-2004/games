# games
# Game Math Simulator (C++)

This project is a **reusable Monte Carlo simulation engine** for analyzing casino-style games in C++.  
It allows you to measure key metrics like **RTP**, **expected value (EV)**, **variance**, **standard deviation**, and **hit rate** for any game that implements the `Game` interface.
In the codebase there is varius games scripts highlow and slots are playable the monte carlo script example is built in with the high low and there are roullete and slot example scripts that just need to be fitted into the simulator.
This code base is a demonstater for casino style statistics and a mean to be used for quick summary of features.
---

## Features

- Modular **RNG wrapper** for consistent random number generation.
- Abstract `Game` interface for easy addition of new games.
- Monte Carlo simulator that can run **millions of trials** efficiently.
- Tracks:
  - RTP (Return to Player)
  - Expected Value (EV)
  - Variance
  - Standard Deviation
  - Hit Rate
- Includes sample games:
  - **High-Low**: Predict if a random number is higher.
  - **3 Slot Machine**: 3-reel slot with configurable symbols and paytable.
  - **5 Slot Machine with rerolls**: 5-reel slot with rerolling when you roll 3 or 4  matchs
  - **Roullete** american style roullete with 0 and 00

---

Additional Notes
this simulation doesn't consider varing bet sizes and in simulating real casino games it approximates game statistics may rise potential issues when bet sizes are considered 
with a house min of 1 and max of 100 mean of 10 sd of 7 the results can vary for that example compared to taking the bet to be 1 every time
