# 🧩 Sudoku Solver (C)

![C](https://img.shields.io/badge/Language-C-blue)
![OpenMP](https://img.shields.io/badge/Parallel-OpenMP-orange)
![License](https://img.shields.io/badge/License-MIT-green)


A **fast, recursive Sudoku Solver** written in C that uses **backtracking** and **parallel processing (OpenMP)** to solve millions of puzzles efficiently from `.csv` files.

---

## | Features

- Solves standard **9×9 Sudoku puzzles**
- Implements **backtracking with recursion**
- Supports **parallel processing (OpenMP)** for batch solving with **multi-threading support**
- Reads puzzles directly from **CSV datasets**
- Tested with Kaggle datasets (✅ 100% accuracy)

---

## | Datasets Used

- [9 Million Sudoku Problems – Rohan Rao (1.48 GB)](https://www.kaggle.com/datasets/rohanrao/sudoku)  
- [1 Million Sudoku Problems – Bryan Park (164 MB)](https://www.kaggle.com/datasets/bryanpark/sudoku)

---

## | How It Works (Algorithm Overview)

The solver uses a **depth-first search backtracking algorithm**.

> According to Wikipedia:  
> “Briefly, a program would solve a puzzle by placing the digit "1" in the first cell and checking if it is allowed to be there. If there are no  violations (checking row, column, and box constraints) then the algorithm advances to the next cell and places a "1" in that cell. When checking for  violations, if it is discovered that the "1" is not allowed, the value is advanced to "2". If a cell is discovered where none of the 9 digits is allowed,  then the algorithm leaves that cell blank and moves back to the previous cell. The value in that cell is then incremented by one. This is repeated until  the allowed value in the last (81st) cell is discovered.”

## | My Implementation

My version expands on this idea using recursion for simplicity and reliability:

1. **Find the next empty cell** (i.e., value = 0).  
   - If none found → puzzle solved → `return true`
2. **Try numbers 1–9**:
   - Check validity:
     - Not in the same **row**
     - Not in the same **column**
     - Not in the same **3×3 subgrid**, *(special logic explanation in the sudoku_solver_heavyweight.c file)*
3. **If valid**, place the number and recursively solve the next cell.
4. **If recursive call succeeds → return true**
5. **Otherwise**, reset the cell (`0`) and try the next number.
6. If no number works → `return false` → backtrack.

## | Performance
- Solves up to **9 million puzzles** in parallel using OpenMP.
- Average solving time per puzzle: **~1–3 ms** (depending on CPU).
- Verified accuracy: **100%** across both Kaggle datasets.



## | Example Usage

### For batch testing

```bash
# Compile with OpenMP and other optimizations (recommended for datasets larger than 1000 problems)
gcc sudoku_solver_heavyweight.c -O3 -fopenmp -march=native -o sudoku_solver_heavyweight.exe
```
```bash
# Compile with just OpenMP (recommended for smaller datasets)
gcc sudoku_solver_heavyweight.c -fopenmp -o sudoku_solver_heavyweight.exe
```
```bash
# Run
./sudoku_solver_heavyweight.exe 
```
### For Single Problem solving
```bash
# Compiling on gcc
gcc sudoku_solver.c  -o sudoku_solver.exe
```
```bash
# Run
./sudoku_solver.exe 
```

## | Future Improvements

1. Add GUI or web interface for visualization

2. Support for variable grid sizes (e.g., 16×16)


## | Dependencies
- **Compiler:** GCC (supports OpenMP)
- **Operating System:** Windows (tested), should work on Linux/macOS with *minor changes*
- **Libraries:** OpenMP (included with GCC)


## | Project Structure
``` 
.
├── sudoku_solver_heavyweight.c        # Main solver code for large batches
├── sudoku_solver.c                    # Solver code for single problems with no multi-threading or OpenMP (not required)
├── sudoku.csv                         # Example CSVs (the 9 million problem dataset)
└── README.md                           # Documentation
```

## | License
This project is open-source under the **MIT License**.
