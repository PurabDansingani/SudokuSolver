#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 9
#define CELL_SIZE 50    // Size of each cell in pixels
#define GRID_X 100      // X-coordinate of the grid's top-left corner
#define GRID_Y 100      // Y-coordinate of the grid's top-left corner
#include <dos.h>
// Function Prototypes
void drawGrid();
void drawNumbers(int board[SIZE][SIZE], int original[SIZE][SIZE]);
int isValid(int board[SIZE][SIZE], int row, int col, int num);
int solveSudoku(int board[SIZE][SIZE], int original[SIZE][SIZE], int *solvedCells, int totalCells);
int inputBoard(int board[SIZE][SIZE]);
void generateSolution(int board[SIZE][SIZE]);
void removeNumbers(int board[SIZE][SIZE], int numToRemove);
int getDifficultyLevel();
int displayMenu();
int findEmptyCell(int board[SIZE][SIZE], int *row, int *col);
void updateCell(int row, int col, int num, int color);
void highlightCell(int row, int col, int color);
void unhighlightCell(int row, int col);
void printBoardConsole(int board[SIZE][SIZE]);

// Function to draw the Sudoku grid using graphics
void drawGrid() {
    int i;
    // Draw the grid lines
    for (i = 0; i <= SIZE; i++) {
	// Thicker lines for 3x3 subgrids
	if (i % 3 == 0) {
	    setlinestyle(SOLID_LINE, 0, 3);
	} else {
	    setlinestyle(SOLID_LINE, 0, 1);
	}
	// Vertical lines
	line(GRID_X + i * CELL_SIZE, GRID_Y, GRID_X + i * CELL_SIZE, GRID_Y + SIZE * CELL_SIZE);
	// Horizontal lines
	line(GRID_X, GRID_Y + i * CELL_SIZE, GRID_X + SIZE * CELL_SIZE, GRID_Y + i * CELL_SIZE);
    }
}                           

// Function to display numbers on the grid
void drawNumbers(int board[SIZE][SIZE], int original[SIZE][SIZE]) {
    int row,col;
    char numStr[2];
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (row = 0; row < SIZE; row++) {
	for (col = 0; col < SIZE; col++) {
	    if (board[row][col] != 0) {
		sprintf(numStr, "%d", board[row][col]);
		// Different color for original numbers
		if (original[row][col] != 0)
		    setcolor(WHITE);
		else
		    setcolor(GREEN);
		outtextxy(GRID_X + col * CELL_SIZE + CELL_SIZE / 3, GRID_Y + row * CELL_SIZE + CELL_SIZE / 4, numStr);
	    }
	}
    }
}

// Function to update a single cell with a number and color
void updateCell(int row, int col, int num, int color) {
    char numStr[2];
    sprintf(numStr, "%d", num);
    setcolor(color);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(GRID_X + col * CELL_SIZE + CELL_SIZE / 3, GRID_Y + row * CELL_SIZE + CELL_SIZE / 4, numStr);
    delay(50); // Pause to show the step
}

// Function to highlight a cell
void highlightCell(int row, int col, int color) {
    setcolor(color);
    rectangle(GRID_X + col * CELL_SIZE, GRID_Y + row * CELL_SIZE,
	      GRID_X + (col + 1) * CELL_SIZE, GRID_Y + (row + 1) * CELL_SIZE);
    delay(50); // Pause to show the highlight
}

// Function to unhighlight a cell
void unhighlightCell(int row, int col) {
    setcolor(BLACK);
    rectangle(GRID_X + col * CELL_SIZE, GRID_Y + row * CELL_SIZE,
	      GRID_X + (col + 1) * CELL_SIZE, GRID_Y + (row + 1) * CELL_SIZE);
    delay(50); // Pause to remove the highlight
}

// Function to draw and update the progress bar
// Function to check if placing a number is valid according to Sudoku rules
int isValid(int board[SIZE][SIZE], int row, int col, int num) {
    // Check the row
    int startRow,startCol;
    int x,i,j;
    for( x = 0; x < SIZE; x++) {
	if (board[row][x] == num)
	    return 0;
    }

    // Check the column
    for ( x = 0; x < SIZE; x++) {
	if (board[x][col] == num)
	    return 0;
    }

    // Check the 3x3 grid
    startRow = row - row % 3;
    startCol = col - col % 3;
    for (i = 0; i < 3; i++) {
	for (j = 0; j < 3; j++) {
	    if (board[startRow + i][startCol + j] == num)
		return 0;
	}
    }

    return 1;
}

// Function to find an empty cell; returns true if found
int findEmptyCell(int board[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
	for (*col = 0; *col < SIZE; (*col)++) {
	    if (board[*row][*col] == 0)
		return 1;
	}
    }
    return 0;
}

// Recursive Backtracking Solver with Graphical Updates
int solveSudoku(int board[SIZE][SIZE], int original[SIZE][SIZE], int *solvedCells, int totalCells) {
    int row, col,num;
    if (!findEmptyCell(board, &row, &col))
	return 1; // Puzzle solved

    // Highlight the current cell
    highlightCell(row, col, YELLOW);

    for (num = 1; num <= 9; num++) {
	if (isValid(board, row, col, num)==1) {
	    board[row][col] = num;
	    updateCell(row, col, num, GREEN); // Update graphical display
	    (*solvedCells)++;
	  

	    if (solveSudoku(board, original, solvedCells, totalCells)==1)
		return 1;

	    board[row][col] = 0;
	    (*solvedCells)--;
	   
	}
    }

    // Unhighlight the cell after trying all numbers
    unhighlightCell(row, col);
    return 0; // Trigger backtracking
}

// Function to input the Sudoku board via console
int inputBoard(int board[SIZE][SIZE]) {
    int row,col,temp;
    printf("Enter the Sudoku puzzle row by row.\n");
    printf("Use 0 for empty cells.\n");
    for (row = 0; row < SIZE; row++) {
	printf("Enter 9 numbers for row %d, separated by spaces: ", row + 1);
	for (col = 0; col < SIZE; col++) {
	    if (scanf("%d", &board[row][col]) != 1) {
		printf("Invalid input. Please enter integers between 0 and 9.\n");
		return 0;
	    }
	    if (board[row][col] < 0 || board[row][col] > 9) {
		printf("Invalid number %d. Please enter integers between 0 and 9.\n", board[row][col]);
		return 0;
	    }
	    // Temporarily set cell to 0 to check validity
	     temp = board[row][col];
	    board[row][col] = 0;
	    if (temp != 0 && !isValid(board, row, col, temp)) {
		printf("Invalid puzzle! Conflict detected at row %d, column %d.\n", row + 1, col + 1);
		return 0;
	    }
	    board[row][col] = temp; // Restore the number
	}
    }
    return 1;
}

// Function to solve the board recursively (standard backtracking without graphical updates)
int solveBoardStandard(int board[SIZE][SIZE]) {
    int row, col,num;
    if (!findEmptyCell(board, &row, &col))
	return 1; // Puzzle solved

    for (num = 1; num <= 9; num++) {
	if (isValid(board, row, col, num)==1) {
	    board[row][col] = num;
	    if (solveBoardStandard(board)==1)
		return 1;
	    board[row][col] = 0; // Backtrack
	}
    }
    return 0; // Trigger backtracking
}

// Function to generate a complete Sudoku solution
void generateSolution(int board[SIZE][SIZE]) {
    // Initialize board to 0
     int row,col,i,j,temp;
     int numbers[9] = {1,2,3,4,5,6,7,8,9};
    for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	    board[row][col] = 0;


    for (i = 8; i > 0; i--) {
	j = rand() % (i + 1);
	// Swap
	 temp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = temp;
    }

    // Place numbers in the first row to start
    for (col = 0; col < SIZE; col++) {
	board[0][col] = numbers[col];
    }

    // Solve the board to generate a solution
    solveBoardStandard(board);
}

// Function to remove numbers from the board based on difficulty
void removeNumbers(int board[SIZE][SIZE], int numToRemove) {
    srand(time(0));
    while (numToRemove > 0) {
	int row = rand() % SIZE;
	int col = rand() % SIZE;
	if (board[row][col] != 0) {
	    board[row][col] = 0;
	    numToRemove--;
	}
    }
}

// Function to choose difficulty level
int getDifficultyLevel() {
    int choice;
    printf("Choose difficulty level:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
	case 1: return 55;  // Easy: 35 cells pre-filled
	case 2: return 45;  // Medium: 45 cells pre-filled
	case 3: return 35;  // Hard: 55 cells pre-filled
	default:
	    printf("Invalid choice, defaulting to Medium difficulty.\n");
	    return 45;
    }
}

// Function to display menu and get user choice
int displayMenu() {
    int choice;
    printf("=== Sudoku Solver ===\n");
    printf("Choose an option:\n");
    printf("1. Input your own Sudoku puzzle\n");
    printf("2. Generate a random Sudoku puzzle\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    return choice;
}

// Function to display the board in the console (optional)
void printBoardConsole(int board[SIZE][SIZE]) {
    int row,col;
    printf("\n");

    for (row = 0; row < SIZE; row++) {
	if (row % 3 == 0 && row != 0)
	    printf("------+-------+------\n");
	for (col = 0; col < SIZE; col++) {
	    if (col % 3 == 0 && col != 0)
		printf("| ");
	    if (board[row][col] == 0)
		printf(".");
	    else
		printf("%d ", board[row][col]);
	}
	printf("\n");
    }
    printf("\n");
}

int main() {
    // Initialize graphics mode
    int numToRemove,totalCells,solvedCells,solvable;
    int board[SIZE][SIZE];
    int originalBoard[SIZE][SIZE]; // To keep track of initial numbers
    int choice = displayMenu();
    int row,col;
    int gd=DETECT,gm;
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");  // Initialize graphics mode

    srand(time(0));  // Seed the random number generator
    if (choice == 1) {
	// User inputs the puzzle
	if (!inputBoard(board)) {
	    printf("Failed to input a valid Sudoku puzzle.\n");
	    getch();
	    closegraph();
	    return 1;
	}
	// Copy board to originalBoard
	for (row = 0; row < SIZE; row++)
	    for (col = 0; col < SIZE; col++)
		originalBoard[row][col] = board[row][col];
    }
    else if (choice == 2) {
	// Generate a random puzzle
	generateSolution(board);
	numToRemove = 81 - getDifficultyLevel();
	removeNumbers(board, numToRemove);
	// Copy board to originalBoard
	for (row = 0; row < SIZE; row++)
	    for (col = 0; col < SIZE; col++)
		originalBoard[row][col] = board[row][col];
    }
    else {
	printf("Invalid choice. Exiting...\n");
	getch();
	closegraph();
	return 1;
    }

    // Draw the initial grid and numbers
    cleardevice(); // Clear the graphical screen
    drawGrid();
    drawNumbers(board, originalBoard);

    // Print the board in the console (optional)
    printf("Initial Sudoku Puzzle:\n");
    printBoardConsole(board);

    // Initialize progress variables
    totalCells = 81;
    solvedCells = 0;
    for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	    if (board[row][col] != 0)
		solvedCells++;
    // Attempt to solve the puzzle
    printf("Solving the puzzle...\n");
    solvable = solveSudoku(board, originalBoard, &solvedCells, totalCells);

    if (solvable) {
	printf("Sudoku Puzzle Solved Successfully!\n");
	// Update the grid with the final numbers
	drawGrid();
	drawNumbers(board, originalBoard);
	// Optionally, display the solved board step-by-step
	for (row = 0; row < SIZE; row++)
	    for (col = 0; col < SIZE; col++)
		if (originalBoard[row][col] == 0) {
		    updateCell(row, col, board[row][col], YELLOW);
		}
	printf("Final Solved Sudoku Puzzle:\n");
	printBoardConsole(board);
    }
    else {
	printf("The Sudoku puzzle is invalid and cannot be solved.\n");
    }

    printf("Press any key to exit...\n");
    getch();
    closegraph();
    return 0;
}

