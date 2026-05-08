# OOP_Project_25F-0572_25F-0549
# ♟️ Chess Game in C++

> A fully playable terminal-based chess game built with Object-Oriented Programming principles.

**Course:** CL1004 – Object Oriented Programming  
**Institution:** National University of Computer & Emerging Sciences (NUCES)  
**Campus:** Faisalabad-Chiniot | Spring 2026

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [OOP Design](#oop-design)
- [Class Hierarchy](#class-hierarchy)
- [Getting Started](#getting-started)
- [How to Play](#how-to-play)
- [Piece Reference](#piece-reference)
- [Game Rules Implemented](#game-rules-implemented)
- [Project Structure](#project-structure)

---

## Overview

This project implements a two-player chess game that runs entirely in the terminal. Players enter moves using standard algebraic notation (e.g., `e2 e4`). The game enforces all standard chess rules including check detection, checkmate, stalemate, and pawn promotion.

---

## Features

- ✅ Full two-player gameplay in the terminal
- ✅ Algebraic notation input (`e2 e4` style)
- ✅ Legal move validation for all 6 piece types
- ✅ Check and checkmate detection
- ✅ Stalemate detection
- ✅ Pawn promotion (Q / R / B / N)
- ✅ Self-check prevention (can't move into check)
- ✅ Resign option (`quit` / `exit`)
- ✅ Custom player names
- ✅ Clear board display with piece legend

---

## OOP Design

The project demonstrates core OOP concepts:

| Concept | Implementation |
|---|---|
| **Abstraction** | `Piece` base class with pure virtual `isValidMove()` |
| **Inheritance** | `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King` extend `Piece` |
| **Polymorphism** | Each piece overrides `isValidMove()` with its own movement logic |
| **Encapsulation** | `Board` manages the grid privately; `Piece` hides internal state |

---

## Class Hierarchy

```
Piece  (abstract base class)
├── Pawn
├── Rook
├── Knight
├── Bishop
├── Queen
└── King

Board  (manages the 8×8 grid and game logic)
```

### Key Methods

**`Piece` (Abstract)**
- `isValidMove(fr, fc, tr, tc, grid)` — pure virtual; each subclass implements its own rules

**`Board`**
- `display()` — renders the board in the terminal
- `isMoveValid()` — delegates to the piece's `isValidMove()`
- `isInCheck(Color)` — checks if a king is under attack
- `hasNoLegalMoves(Color)` — used to detect checkmate and stalemate
- `tempMove()` / `undoTemp()` — simulate a move to test for self-check
- `findKing(Color)` — locates the king on the board

---

## Getting Started

### Prerequisites

- A C++ compiler supporting **C++11** or later (g++, clang++, MSVC)

### Compile

```bash
g++ -o chess chess.cpp -std=c++11
```

### Run

```bash
./chess
```

On Windows:
```bash
chess.exe
```

---

## How to Play

1. Run the program and enter both player names when prompted.
2. The board is displayed after each move.
3. Enter your move as two space-separated squares:

```
White's move (e.g. e2 e4): e2 e4
```

4. Files are labeled `a–h` (left to right) and ranks `1–8` (bottom to top).
5. Type `quit` or `exit` to resign at any time.

### Example Opening Moves

```
e2 e4    # White pawn advances
e7 e5    # Black pawn responds
g1 f3    # White knight develops
```

### Board Layout

```
     a   b   c   d   e   f   g   h
   +---+---+---+---+---+---+---+---+
 8 | r | n | b | q | k | b | n | r | 8
   +---+---+---+---+---+---+---+---+
 7 | p | p | p | p | p | p | p | p | 7
   +---+---+---+---+---+---+---+---+
 6 | . | . | . | . | . | . | . | . | 6
   ...
 1 | R | N | B | Q | K | B | N | R | 1
   +---+---+---+---+---+---+---+---+
     a   b   c   d   e   f   g   h
```

---

## Piece Reference

| Symbol | Piece | Color |
|---|---|---|
| `K` | King | White |
| `Q` | Queen | White |
| `R` | Rook | White |
| `B` | Bishop | White |
| `N` | Knight | White |
| `P` | Pawn | White |
| `k` | King | Black |
| `q` | Queen | Black |
| `r` | Rook | Black |
| `b` | Bishop | Black |
| `n` | Knight | Black |
| `p` | Pawn | Black |

> **UPPER** = White &nbsp;|&nbsp; **lower** = Black

---

## Game Rules Implemented

| Rule | Status |
|---|---|
| Piece-specific movement | ✅ |
| Path obstruction checks | ✅ |
| Capturing enemy pieces | ✅ |
| Cannot capture own pieces | ✅ |
| Check detection | ✅ |
| Moving into check prevention | ✅ |
| Checkmate detection | ✅ |
| Stalemate detection | ✅ |
| Pawn two-square first move | ✅ |
| Pawn diagonal capture | ✅ |
| Pawn promotion | ✅ |


---

## Project Structure

```
chess.cpp          # All source code in a single file
README.md          # This file
```


---

## License

This project was developed for academic purposes as part of the CL1004 OOP course at NUCES Faisalabad-Chiniot.
