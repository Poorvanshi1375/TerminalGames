#include <bits/stdc++.h>
using namespace std;

const int ROWS = 5;
const int COLUMNS = 5;
const int MINES = 5;

struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    int adjacentMines = 0;
};

vector<vector<Cell>> grid;

// Function to reset and initialize the grid
void initializeGrid() {
    grid.assign(ROWS, vector<Cell>(COLUMNS)); // Reset the grid
}

// Function to print the grid
void printGrid() {
    cout << "  ";
    for (int i = 0; i < COLUMNS; i++) cout << i << " ";
    cout << "\n  " << string(COLUMNS * 2, '-') << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << i << " |";
        for (int j = 0; j < COLUMNS; j++) {
            if (!grid[i][j].isRevealed) {
                cout << " *";
            } else if (grid[i][j].isMine) {
                cout << " X";
            } else {
                cout << " " << grid[i][j].adjacentMines;
            }
        }
        cout << endl;
    }
}

// Function to place mines randomly
void placeMines() {
    int placedMines = 0;
    while (placedMines < MINES) {
        int r = rand() % ROWS;
        int c = rand() % COLUMNS;
        if (!grid[r][c].isMine) {
            grid[r][c].isMine = true;
            ++placedMines;
        }
    }
}

// Function to calculate adjacent mine counts
void calculateAdjacentMines() {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j].isMine) continue;

            int count = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLUMNS && grid[ni][nj].isMine) {
                    count++;
                }
            }
            grid[i][j].adjacentMines = count;
        }
    }
}

// Function to reveal a cell
bool revealCell(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLUMNS || grid[r][c].isRevealed) return true;
    
    grid[r][c].isRevealed = true;
    
    if (grid[r][c].isMine) return false; // Hit a mine - Game over

    // If no adjacent mines, reveal surrounding cells
    if (grid[r][c].adjacentMines == 0) {
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int d = 0; d < 8; d++) {
            int ni = r + dx[d], nj = c + dy[d];
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLUMNS && !grid[ni][nj].isRevealed) {
                revealCell(ni, nj);
            }
        }
    }
    return true;
}

// Function to check if the player has won
bool checkWin() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (!grid[i][j].isMine && !grid[i][j].isRevealed) {
                return false; // There are still unrevealed non-mine cells
            }
        }
    }
    return true;
}

// Game loop
void playGame() {
    initializeGrid();
    placeMines();
    calculateAdjacentMines();

    while (true) {
        printGrid();
        
        int r, c;
        cout << "Enter row and column to reveal (e.g., 2 3): ";
        cin >> r >> c;

        if (!revealCell(r, c)) {
            printGrid();
            cout << "Boom! You hit a mine. Game Over!\n";
            return;
        }

        if (checkWin()) {
            printGrid();
            cout << "Congratulations! You cleared the minefield!\n";
            return;
        }
    }
}

int main() {
    srand(time(0)); // Seed random once at program start
    cout << "Welcome to Minesweeper!\n";
    playGame();
    return 0;
}
