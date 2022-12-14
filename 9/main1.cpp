#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <iomanip>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <cstdlib>

using namespace std;

#define GRID_SIZE 50
typedef tuple <int, int> ituple;

char grid[GRID_SIZE][GRID_SIZE];
ituple HLoc {GRID_SIZE-1,0};
ituple HPrevLoc {GRID_SIZE-1,0};
ituple TLoc {GRID_SIZE-1,0};
ituple TPrevLoc{GRID_SIZE-1,0};
set<ituple> coveredCells {};
int counter {0};

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

bool isAdjacent(ituple t1, ituple t2) {
    // cout << t1[0] << endl;
    // if (grid[get<0>(t1)][get<1>(t1)]   )
    int rowSeparation = abs(get<0>(t1) - get<0>(t2));
    int colSeparation = abs(get<1>(t1) - get<1>(t2));

    // cout << "rowS:" << rowSeparation << endl;
    // cout << "colS:" << colSeparation << endl;
    if (rowSeparation < 2 && colSeparation < 2) {
        return true;
    }
    return false;
}

void updateGrid() {
    // int row =get<1>(HLoc);
    grid[get<0>(HLoc)][get<1>(HLoc)] = 'H';
    grid[get<0>(HPrevLoc)][get<1>(HPrevLoc)] = ' ';
    // check if T is adjacent
    if (isAdjacent(HLoc, TLoc)) {
        // cout << "here" << endl;
        grid[get<0>(TLoc)][get<1>(TLoc)] = 'T';
    } else {
        // cout << "here 2" << endl;
        grid[get<0>(TLoc)][get<1>(TLoc)] = 'X';
        // get<1>(TLoc) += 1;
        TLoc = HPrevLoc;
        grid[get<0>(HPrevLoc)][get<1>(HPrevLoc)] = 'T';
        if (!coveredCells.contains(ituple {get<0>(HPrevLoc), get<1>(HPrevLoc)})) {
            counter++;
            coveredCells.insert(ituple {get<0>(HPrevLoc), get<1>(HPrevLoc)});
        }
    }
    // printGrid();
    // printLocations();
}

void walk(char direction, int distance) {
    ituple destLoc = HLoc;
    switch (direction) {
        case 'U':
            if ((get<0>(HLoc) - distance) < 0) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                // get<0>(HLoc) -= distance;
                get<0>(destLoc) -= distance;
                // get<1>(HLoc) += distance;
                for (; get<0>(HPrevLoc) > get<0>(destLoc); get<0>(HPrevLoc) -=1) {
                    get<0>(HLoc) -= 1;
                    updateGrid();
                }
            }
            break;
        case 'R':
            if ((get<1>(HLoc) + distance) > GRID_SIZE - 1) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<1>(destLoc) += distance;

                // get<1>(HLoc) += distance;
                for (; get<1>(HPrevLoc) < get<1>(destLoc); get<1>(HPrevLoc) +=1) {
                    get<1>(HLoc) += 1;
                    updateGrid();
                }
            }
            break;
        case 'D':
            if ((get<0>(HLoc) + distance) > GRID_SIZE - 1) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                // get<0>(HLoc) += distance;
                get<0>(destLoc) += distance;
                // get<1>(HLoc) += distance;
                for (; get<0>(HPrevLoc) < get<0>(destLoc); get<0>(HPrevLoc) +=1) {
                    get<0>(HLoc) += 1;
                    updateGrid();
                }
            }
            break;
        case 'L':
            if ((get<1>(HLoc) - distance) < 0) {
                cout << "out of bound" << endl;
            } else {
                HPrevLoc = HLoc;
                get<1>(destLoc) -= distance;

                // get<1>(HLoc) += distance;
                for (; get<1>(HPrevLoc) > get<1>(destLoc); get<1>(HPrevLoc) -=1) {
                    get<1>(HLoc) -= 1;
                    updateGrid();
                }            
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
    grid[GRID_SIZE-1][0] = 'H';
}

void printCoveredCells() {
    for (auto cell : coveredCells) {
        cout << "(" << get<0>(cell) << "," << get<1>(cell) << ")" << ", ";
    }
    cout << endl;
}

//AOC Day 9 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    char direction {};
    int distance {};
    createGrid();
    // printGrid();
    while (getline(file, line)) {
        cout << line << endl;
        direction = line.substr(0, line.find(" "))[0];
        distance = line.substr(line.find(" ")+1)[0] - 48;
        // cout << "direction: " << direction << endl;
        // cout << "distance: " << distance << endl;
        walk(direction, distance);
    }
    // walk(0,0);
    // ituple t1 {5,0};
    // ituple t2 {4,1};


    // isAdjacent(t1, t2);
    // printLocations();
    printCoveredCells();
    cout << "Max Size:" << coveredCells.max_size() << endl;
    cout << "Counter: " << counter << endl;
    cout << "Answer: " << coveredCells.size() << endl;
}