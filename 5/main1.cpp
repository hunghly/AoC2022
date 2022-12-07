#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

#define GRID_SIZE 50

/*
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3
*/
// char grid[GRID_SIZE][GRID_SIZE] = 
//                 {
//                 {},
//                 {},
//                 {},
//                 {},
//                 {},
//                 {},
//                 {'\0','D','\0'},
//                 {'N','C','\0'},
//                 {'Z','M','P'}};


/*
[H]                 [Z]         [J]
[L]     [W] [B]     [G]         [R]
[R]     [G] [S]     [J] [H]     [Q]
[F]     [N] [T] [J] [P] [R]     [F]
[B]     [C] [M] [R] [Q] [F] [G] [P]
[C] [D] [F] [D] [D] [D] [T] [M] [G]
[J] [C] [J] [J] [C] [L] [Z] [V] [B]
[M] [Z] [H] [P] [N] [W] [P] [L] [C]
 1   2   3   4   5   6   7   8   9 
*/

char grid[GRID_SIZE][GRID_SIZE] = 
                {
                {},{},
                {},{},{},{},{},{},{},{},
                {},{},{},{},{},{},{},{},
                {},{},{},{},{},{},{},{},
                {},{},{},{},{},{},{},{},
                {},{},{},{},{},{},{},{},
                {'H','\0','\0','\0','\0','Z','\0','\0','J'},
                {'L','\0','W','B','\0','G','\0','\0','R'},
                {'R','\0','G','S','\0','J','H','\0','Q'},
                {'F','\0','N','T','J','P','R','\0','F'},
                {'B','\0','C','M','R','Q','F','G','P'},
                {'C','D','F','D','D','D','T','M','G'},
                {'J','C','J','J','C','L','Z','V','B'},
                {'M','Z','H','P','N','W','P','L','C'}};
void printGrid() {
    for (int row = 0; row < GRID_SIZE; row++) {
        cout << setw(2) << std::left << row << "  ";
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != '\0') {
                cout << "[" << grid[row][col] << "]";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
    // column numbers
    cout << "    ";
    for (int col = 0; col < GRID_SIZE; col++) {
        cout << " " << (col+1) << " ";
    }
    cout << endl;
}

// returns the top row based on column
int findTopRow(int col) {
    for (int row = 0; row < GRID_SIZE; row++) {
        if (grid[row][col] != '\0') {
            return row;
        }
    }
    // If no empty rows, just return bottom of stack
    return GRID_SIZE;
}

// move columns
void move(int oldCol, int newCol, int numBlocks) {
    int topRowOldCol;
    int emptyRow;
    char crateID;
    for (int i = 0; i < numBlocks; i++) {
        crateID = '\0';
        topRowOldCol = findTopRow(oldCol);
        crateID = grid[topRowOldCol][oldCol];
        // empty row will be top row minus 1
        emptyRow = findTopRow(newCol)-1;
        grid[emptyRow][newCol] = crateID;
        cout << "Moved crateID:" << crateID << " to " << "(" << emptyRow << "," << newCol << ")" << endl;
        // Remove old crate
        grid[topRowOldCol][oldCol] = '\0';
    }
    printGrid();
}


//AOC Day 5 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    string token;
    int numBlocks {};
    int oldCol {};
    int newCol {};
    printGrid();
    while (getline(file, line)) {
        cout << line << endl;
        stringstream ss(line);
        while(getline(ss, token, ' ')) {
            if (token == "move") {
                getline(ss, token, ' ');
                numBlocks = stoi(token);
            } else if (token == "from") {
                getline(ss, token, ' ');
                oldCol = stoi(token);
            } else if (token == "to") {
                getline(ss, token, ' ');
                newCol = stoi(token);
            }
        }
        move(oldCol-1, newCol-1, numBlocks);
    }
}