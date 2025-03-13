# SudokuSolver
This program is a Graphical Sudoku Solver using C and the BGI graphics library. It allows the user to either input a Sudoku puzzle manually or generate a random Sudoku puzzle and then solve it using backtracking with visual updates.

Key Features and Approach
Graphical Interface (BGI Graphics Library)

The Sudoku grid is drawn using drawGrid().
Numbers are displayed using drawNumbers().
Updates are made cell by cell (updateCell()).
Highlights cells while solving (highlightCell() and unhighlightCell()).
Backtracking Algorithm for Solving Sudoku

The core solving logic is based on recursive backtracking (solveSudoku()).
The function attempts to place a valid number in an empty cell.
If a number leads to an unsolvable state, it backtracks and tries a different number.
Board Input and Validation

The user can manually input a puzzle (inputBoard()).
If an invalid move is detected, the input is rejected.
The program also allows random puzzle generation (generateSolution() and removeNumbers()).
Difficulty Selection

The user can choose a difficulty level (getDifficultyLevel()).
More numbers are removed for harder difficulty levels.
Graphical Updates During Solving

While solving, the program highlights and updates each cell visually.
Algorithm and Time Complexity Analysis

  1. Backtracking Approach
  This program solves the Sudoku using recursive backtracking.
  The algorithm tries filling empty cells one by one with numbers from 1 to 9.
  If placing a number violates Sudoku rules, it backtracks and tries another number.
  It continues until the board is completely solved or deemed unsolvable.

  2. Time Complexity
  The worst-case time complexity is O(9^(N*N)), where N = 9.
  In the worst case, all 81 cells need to be filled, and each can have 9 possibilities.
  However, with pruning techniques (like checking row, column, and 3×3 grid constraints early), the average case runs much faster.
  
  3. Space Complexity
  The space complexity is O(N^2) = O(81) = O(1).
  It only stores the 9x9 board, which is a constant-sized structure.
  The recursive call stack depth is at most 81 in the worst case.

Summary
  Type of Approach: Recursive Backtracking with graphical updates.
  Worst-Case Time Complexity: O(9^(N*N)) (Exponential).
  Average-Case Time Complexity: Much faster due to pruning.
  Space Complexity: O(1) (constant-size 9x9 board).
  This program effectively visualizes the solving process while using a standard backtracking approach to solve Sudoku puzzles. 🚀
