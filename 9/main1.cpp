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
tuple <int, int> HLoc {GRID_SIZE-1,0};
tuple <int, int> HPrevLoc {GRID_SIZE-1,0};
tuple <int, int> TLoc {GRID_SIZE-1,0};
tuple <int, int> TPrevLoc{GRID_SIZE-1,0};

void printLocations() {
    cout << "(" << get<0>(HLoc) << "," << get<1>(HLoc) << "): HLoc" << endl;
    cout << "(" << get<0>(HPrevLoc) << "," << get<1>(HPrevLoc) << "): HPrevLoc" << endl;
    cout << "(" << get<0>(TLoc) << "," << get<1>(TLoc) << "): TLoc" << endl;
    cout << "(" << get<0>(TPrevLoc) << "," << get<1>(TPrevLoc) << "): TPrevLoc" << endl;

}
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
            cout << " " << (col) << " ";
        } else {
            cout << " " << (col) << "  ";
        }
    }
    cout << endl;
}

void updateGrid() {
    int row =get<1>(HLoc);
    grid[get<0>(HLoc)][get<1>(HLoc)] = 'H';
    grid[get<0>(HPrevLoc)][get<1>(HPrevLoc)] = ' ';

}

void walk(char direction, int distance) {
    switch (direction) {
        case 'U':
            if ((get<0>(HLoc) - distance) < 0) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<0>(HLoc) -= distance;
            }
            break;
        case 'R':
            if ((get<1>(HLoc) + distance) > GRID_SIZE - 1) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<1>(HLoc) += distance;
            }
            break;
        case 'D':
            if ((get<0>(HLoc) + distance) > GRID_SIZE - 1) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<0>(HLoc) += distance;
            }
            break;
        case 'L':
            if ((get<1>(HLoc) - distance) < 0) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<1>(HLoc) -= distance;
            }
            break;
        default:
            break;
    }
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
    char direction {};
    int distance {};
    createGrid();
    printGrid();
    while (getline(file, line)) {
        cout << line << endl;
        direction = line.substr(0, line.find(" "))[0];
        distance = line.substr(line.find(" ")+1)[0] - 48;
        // cout << "direction: " << direction << endl;
        // cout << "distance: " << distance << endl;
        walk(direction, distance);
        updateGrid();
        printLocations();
        printGrid();

    }
    walk(0,0);
    printLocations();
}