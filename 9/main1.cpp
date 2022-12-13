#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <tuple>

using namespace std;

#define GRID_SIZE 20

char grid[GRID_SIZE][GRID_SIZE];
tuple <int, int> HLoc {0,0};
tuple <int, int> TLoc {0,0};


void printGrid() {
    for (int row = 0; row < GRID_SIZE; row++) {
        cout << setw(2) << std::left << row << "  ";
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != '\0') {
                cout << "[" << grid[row][col] << "]" << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    // column numbers
    cout << "    ";
    for (int col = 0; col < GRID_SIZE; col++) {
        if ((col+1) > 8) {
            cout << " " << (col+1) << " ";
        } else {
            cout << " " << (col+1) << "  ";
        }
    }
    cout << endl;
}

void createGrid() {
    std::for_each(std::begin(grid), std::end(grid), [](auto &row) {
        std::fill(std::begin(row), std::end(row), ' ');
    });
}

//AOC Day 9 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    createGrid();
    printGrid();
    while (getline(file, line)) {
        cout << line << endl;
    }
}