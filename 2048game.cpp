#include <bits/stdc++.h>
using namespace std;

const int grid_size = 4;

//to print the grid
void printGrid(int grid[grid_size][grid_size]) {
    system("cls");
    cout << "2048 Game!\n\n";
    cout << "Use W (Up), A (Left), S (Down), D (Right), Q (Quit)\n\n";
    
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid[i][j] == 0) cout << setw(5) << ".";
            else cout << setw(5) << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

//to add random tile (2 or 4)
bool addRandomTile(int grid[grid_size][grid_size]) {
    vector<pair<int, int>> emptyCells;
    
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid[i][j] == 0) emptyCells.push_back({i, j});
        }
    }

    if (emptyCells.empty()) return false;

    int index = rand() % emptyCells.size();
    grid[emptyCells[index].first][emptyCells[index].second] = (rand() % 2 + 1) * 2; // 2 or 4
    return true;
}

//to slide tiles in a given direction
bool slideAndMerge(int grid[grid_size][grid_size], int dx, int dy) {
    bool moved = false;

    // Define iteration order to move in the correct direction
    int start = (dx == 1 || dy == 1) ? grid_size - 1 : 0;
    int end = (dx == 1 || dy == 1) ? -1 : grid_size;
    int step = (dx == 1 || dy == 1) ? -1 : 1;

    // Move tiles
    for (int _ = 0; _ < grid_size; ++_) {
        for (int i = start; i != end; i += step) {
            for (int j = start; j != end; j += step) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < grid_size && nj >= 0 && nj < grid_size && grid[i][j] != 0 && grid[ni][nj] == 0) {
                    grid[ni][nj] = grid[i][j];
                    grid[i][j] = 0;
                    moved = true;
                }
            }
        }
    }

    // Merge tiles
    for (int i = start; i != end; i += step) {
        for (int j = start; j != end; j += step) {
            int ni = i + dx, nj = j + dy;
            if (ni >= 0 && ni < grid_size && nj >= 0 && nj < grid_size && grid[i][j] == grid[ni][nj] && grid[i][j] != 0) {
                grid[ni][nj] *= 2;
                grid[i][j] = 0;
                moved = true;
            }
        }
    }

    // Move again after merging to fill gaps
    for (int _ = 0; _ < grid_size; ++_) {
        for (int i = start; i != end; i += step) {
            for (int j = start; j != end; j += step) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < grid_size && nj >= 0 && nj < grid_size && grid[i][j] != 0 && grid[ni][nj] == 0) {
                    grid[ni][nj] = grid[i][j];
                    grid[i][j] = 0;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

//to check if any move is possible
bool canMove(int grid[grid_size][grid_size]) {
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            if (grid[i][j] == 0) return true; // Empty cell exists
            if (i + 1 < grid_size && grid[i][j] == grid[i + 1][j]) return true; // Vertical merge possible
            if (j + 1 < grid_size && grid[i][j] == grid[i][j + 1]) return true; // Horizontal merge possible
        }
    }
    return false;
}

// Main game loop
int main() {
    srand(static_cast<unsigned>(time(0)));

    int grid[grid_size][grid_size] = {0};
    addRandomTile(grid);
    addRandomTile(grid);

    char move;
    bool moved;

    while (true) {
        printGrid(grid);

        if (!canMove(grid)) {
            cout << "Game Over! No more moves possible.\n";
            break;
        }

        cout << "Enter your move: ";
        cin >> move;
        move = tolower(move); 

        moved = false;
        if (move == 'w') moved = slideAndMerge(grid, -1, 0); // Up
        else if (move == 's') moved = slideAndMerge(grid, 1, 0); // Down
        else if (move == 'a') moved = slideAndMerge(grid, 0, -1); // Left
        else if (move == 'd') moved = slideAndMerge(grid, 0, 1); // Right
        else if (move == 'q') break; // Quit
        else {
            cout << "Invalid move! Use W, A, S, D to move or Q to quit.\n";
            continue;
        }

        if (moved) addRandomTile(grid); // Add a random tile only if a move happened
    }

    cout << "Thank you for playing!\n";
    return 0;
}