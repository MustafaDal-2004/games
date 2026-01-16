# games
# Game Math Simulator (C++)

This project is a **reusable Monte Carlo simulation engine** for analyzing casino-style games in C++.  
It allows you to measure key metrics like **RTP**, **expected value (EV)**, **variance**, **standard deviation**, and **hit rate** for any game that implements the `Game` interface.
In the codebase there is varius games scripts highlow and slots are playable the monte carlo script example is built in with the high low and there are roullete and slot example scripts that just need to be fitted into the simulator.
This code base is a demonstater for casino style statistics and a mean to be used for quick summary of features.
There is also a additional model MonteCarloVarBet meaning varying bets to simulate aproximate earning based on max bet min bet and a exponentail distrubuition.
---

## Features

- Modular **RNG wrapper** for consistent random number generation.
- Abstract `Game` interface for easy addition of new games.
- Monte Carlo simulator that can run **millions of trials** efficiently.
- Monte Carlo with varying bets to simulate aproximate returns for a given bet pattern.
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
  - **CompliantSlots** use a single random rumber and enumarates all possible spins given bet return spin result and payout

---

Additional Notes
Some of these games above do not pass compliance and currently use multiple RNG theoughout
this is for easy probability calculation to compare monte carlo with calculated probability.
The reels on the slot machines also are fair with now weighting on specific options.

