# 🪨 Rock, Paper, Scissors, Lizard, Spock – Terminal Game in C

A multi-version terminal game based on the classic hand game, built in **C** and designed with a **clean, presentable interface**. The project evolved through three stages — starting with the original *RPSLS* inspired by **The Big Bang Theory**, then expanding with new mechanics and advanced logic in further extensions.

---

## 🎮 Game Modes (All Versions)

All versions of the game support **3 modes**, allowing players to choose how they want to play:

1. **Human vs Human**  
   Two players take turns entering their moves.

2. **Human vs Computer**  
   The computer makes random moves using `rand()`.

3. **Computer vs Computer**  
   Both players are AI-controlled — great for simulations and testing.

### 🏆 Match Format:
- **First to 4 wins**  
  The game continues in rounds until either player reaches 4 victories.

---

## 🔹 Original Version – RPSLS (5 Moves)

### Moves:
- Rock  
- Paper  
- Scissors  
- Lizard  
- Spock  

> Inspired by *The Big Bang Theory*, this version balances the game with 5 choices to reduce the chance of ties.

### Win Conditions:
A static rule set defines who beats whom (e.g., "Rock crushes Lizard", "Spock smashes Scissors").

### Key Features:
- 5 static moves with hardcoded logic
- 3 game modes
- Clean terminal interface with round-by-round feedback
- First to 4 wins

---

## 🔸 Extension 1 – Elemental Expansion (7 Moves)

### New Moves:
- Fire  
- Water  
- Earth  
- Air  
- Plus: Rock, Paper, Scissors

> This version introduces **7 elemental-themed moves**, and expanding complexity.

### Win Conditions:
Each element has predefined strengths and weaknesses (e.g., "Water beats Fire", "Earth absorbs Water"). These are handled using extended logic via `switch` cases.

### Enhancements:
- More balanced interactions with unique flavor
- Expanded win conditions to match 7-choice logic
- Continued support for all 3 game modes

---

## 🔸 Extension 2 – Mathematical Engine (N Moves)

> The final version introduces **dynamic win/lose logic** based on mathematical relationships — no need to hardcode outcomes!

### How It Works:
- Player choices are mapped to numbers (e.g., Rock = 0, Paper = 1, etc.)
- A formula determines winners based on modulo logic:
