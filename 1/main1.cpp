#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//AOC Day 1 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    int max {0};
    int sum {0};
    while (getline(file, line)) {
        if (line == "" ) {
            // Compare calories
            if (sum > max)
                max = sum;
            sum = 0;
            continue;
        }
        sum += stoi(line);
    }
    cout << "Answer is: " << max << endl;
}