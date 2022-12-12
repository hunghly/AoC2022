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

    int calculateViewDistance(int row, int col, int side) {
        // bool isVisible = false;
        // cout << "Checking: " << treeMap[row][col] << endl;
        int count {0};
        switch (side) {
            case TOP:
                for (int rowStart = row-1; rowStart >= 0; rowStart--) {
                    // cout << "Verifying w/" << treeMap[rowStart][col] << endl;
                    count++;
                    // if (rowStart == 0) {
                    //     break;
                    // }
                    if (treeMap[rowStart][col] >= treeMap[row][col]) {
                        cout << "top side blocked by: " << treeMap[rowStart][col] << endl;
                        break;
                    }
                }
                break;
            case RIGHT:
                for (int colStart = col+1; colStart < colSize; colStart++) {
                    // cout << "Verifying w/" << treeMap[row][colStart] << endl;
                    count++;
                    if (treeMap[row][colStart] >= treeMap[row][col]) {
                        cout << "Right side blocked by: " << treeMap[row][colStart] << endl;
                        break;
                    }
                }
                break;
            case BOTTOM:
                for (int rowStart = row+1; rowStart < rowSize; rowStart++) {
                    // cout << "Verifying w/" << treeMap[rowStart][col] << endl;
                    count++;
                    if (treeMap[rowStart][col] >= treeMap[row][col]) {
                        cout << "bottom side blocked by: " << treeMap[rowStart][col] << endl;
                        break;
                    }
                }
                break;
            case LEFT:
                for (int colStart = col-1; colStart >= 0; colStart--) {
                    // cout << "Verifying w/" << treeMap[row][colStart] << endl;
                    count++;
                    if (treeMap[row][colStart] >= treeMap[row][col]) {
                        cout << "Left side blocked by: " << treeMap[row][colStart] << endl;
                        break;
                    }
                }
                break;
            default:
                return count;
        }
        return count;
    }

    int calculateScenicScore(int row, int col) {
        return calculateViewDistance(row, col, TOP) *
               calculateViewDistance(row, col, RIGHT) *
               calculateViewDistance(row, col, BOTTOM) *
               calculateViewDistance(row, col, LEFT);
    }

    int getBestView() {
        int maxScenicScore {0};
        int tmpScore {0};
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                tmpScore = calculateScenicScore(row, col);
                if (tmpScore > maxScenicScore) {
                    maxScenicScore = tmpScore;
                    cout << "New Max Scenic Score" << maxScenicScore << endl;
                }
            }
        }
        return maxScenicScore;
    }
};




//AOC Day 8 Part 2
int main() {
    ifstream file {"input1.txt"};
    string treeRow;
    vector<int> row {};
    TreeMap map {};
    while (getline(file, treeRow)) {
        // buildTree
        for (char tree : treeRow) {
            row.push_back(tree - 48);
        }
        map.addRow(row);
        row.clear();
    }
    map.printMap();
    map.updateMapSize();
    int answer = map.getBestView();
    cout << "Answer: " << answer;
}