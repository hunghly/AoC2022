/** COMPILE WITH C++ 20
***/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iterator>
#include <iomanip>

using namespace std;


vector<vector<int>> treeMap {};
int rowSize {0};
int colSize {0};

void printRow(vector<int> row) {
    for (int i : row) {
        cout << "[" << i << "]";
    }
    cout << endl;
}

void printMap() {
    for (auto row : treeMap) {
        printRow(row);
    }
}

bool isVisible(int row, int col) {
    cout << "Columns:" << treeMap.size() << endl;
}


//AOC Day 6 Part 1
int main() {
    ifstream file {"input1.txt"};
    string treeRow;
    vector<int> row {};
    while (getline(file, treeRow)) {
        // buildTree
        for (char tree : treeRow) {
            row.push_back(tree - 48);
        }
        treeMap.push_back(row);
        row.clear();
    }
    printMap();
    
    // Check each item in row
    isVisible(0,0);
}