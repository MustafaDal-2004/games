# games
# Game Math Simulator (C++)

This project is a **reusable Monte Carlo simulation engine** for analyzing casino-style games in C++.  
It allows you to measure key metrics like **RTP**, **expected value (EV)**, **variance**, **standard deviation**, and **hit rate** for any game that implements the `Game` interface.

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
  - **Slot Machine**: 3-reel slot with configurable symbols and paytable.

---
