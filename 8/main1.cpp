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

class TreeMap {
public:
    vector<vector<int>> treeMap {};
    int rowSize {0};
    int colSize {0};
    enum Side { TOP, RIGHT, BOTTOM, LEFT};

    void addRow(vector<int> row) {
        treeMap.push_back(row);
    }

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
    void updateMapSize() {
        int c = 0;
        // grab the first row and count how many digits
        for (auto digit : treeMap[0]) {
            c++;
        }

        this->rowSize = c;
        this->colSize = treeMap.size();
        cout << "Columns: " << colSize << " Rows: " << rowSize << endl;
    }

    bool isVisible(int row, int col, int side) {
        bool isVisible = false;
        switch (side) {
            case TOP:
                for (int rowStart = 0; rowStart <= row; rowStart++) {
                    // when we reach the column of the target cell, then exit
                    if (rowStart == row) {
                        cout << "top side visible" << endl;
                        isVisible = true;
                        break;
                    }
                    if (treeMap[rowStart][col] >= treeMap[row][col]) {
                        cout << "top side blocked by: " << treeMap[rowStart][col] << endl;
                        isVisible = false;
                        break;
                    }
                }
                break;
            case RIGHT:
                for (int colStart = colSize - 1; colStart >= col; colStart--) {
                    // when we reach the column of the target cell, then exit
                    if (colStart == col) {
                        cout << "Right side visible" << endl;
                        isVisible = true;
                        break;
                    }
                    if (treeMap[row][colStart] >= treeMap[row][col]) {
                        cout << "Right side blocked by: " << treeMap[row][colStart] << endl;
                        isVisible = false;
                        break;
                    }
                }
                break;
            case BOTTOM:
                for (int rowStart = rowSize-1; rowStart >= row; rowStart--) {
                    // when we reach the column of the target cell, then exit
                    if (rowStart == row) {
                        cout << "bottom side visible" << endl;
                        isVisible = true;
                        break;
                    }
                    if (treeMap[rowStart][col] >= treeMap[row][col]) {
                        cout << "bottom side blocked by: " << treeMap[rowStart][col] << endl;
                        isVisible = false;
                        break;
                    }
                }
                break;
            case LEFT:
                for (int colStart = 0; colStart <= col; colStart++) {
                    // when we reach the column of the target cell, then exit
                    if (colStart == col) {
                        cout << "Left side visible" << endl;
                        isVisible = true;
                        break;
                    }
                    if (treeMap[row][colStart] >= treeMap[row][col]) {
                        cout << "Left side blocked by: " << treeMap[row][colStart] << endl;
                        isVisible = false;
                        break;
                    }
                }
                break;
            default:
                return false;
        }
        // cout << "returning " << isVisible << endl;
        return isVisible;
    }

    // Returns true if any portion is visible
    bool isVisible(int row, int col) {
        // cout << " huh?" << (0 || 0 || 0 || 0) << endl;
        return (isVisible(row, col, TOP) || 
               isVisible(row, col, RIGHT) ||
               isVisible(row, col, BOTTOM) ||
               isVisible(row, col, LEFT));
    }

    // Returns true only if all portions are visible
    bool isFullyVisible(int row, int col) {
        return isVisible(row, col, TOP) && 
               isVisible(row, col, RIGHT) &&
               isVisible(row, col, BOTTOM) &&
               isVisible(row, col, LEFT);
    }

    int countVisibles() {
        int visibleCount {0};
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                if (isVisible(row, col)) {
                    visibleCount++;
                }
                cout << visibleCount << endl;
            }
        }
        return visibleCount;
    }
};




//AOC Day 6 Part 1
int main() {
    ifstream file {"input1.txt"};
    string treeRow;
    vector<int> row {};
    TreeMap map {};
    while (getline(file, treeRow)) {
        // buildTree
        for (char tree : treeRow) {
            // map.addRow(tree - 48);
            row.push_back(tree - 48);
        }
        map.addRow(row);
        row.clear();
    }
    map.printMap();
    map.updateMapSize();
    
    // Check each item in row
    // map.isVisible(1,1,map.Side::TOP);
    // map.isFullyVisible(3,3);
    // map.isVisible(2,3);
    cout << "Answer: " << map.countVisibles() << endl;
}