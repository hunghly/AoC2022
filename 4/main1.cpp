#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> getRange(string elf) {
    vector<int> v {};
    string delim = "-";
    int min = stoi(elf.substr(0, elf.find(delim)));
    int max = stoi(elf.substr(elf.find(delim)+1));
    v.push_back(min);
    v.push_back(max);
    return v;
}

bool inRange(int min, int max, int val) {
    return (min <= val && val <= max);
}

// check if elf1 or elf2 are fully contained in each other
bool doesFullyContain(string elf1, string elf2) {
    vector<int> e1 = getRange(elf1);
    vector<int> e2 = getRange(elf2);
    if (inRange(e1[0], e1[1], e2[0]) && inRange(e1[0], e1[1], e2[1])) {
        return true;
    } else if (inRange(e2[0], e2[1], e1[0]) && inRange(e2[0], e2[1], e1[1])) {
        return true;
    }
    return false;
}

//AOC Day 4 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    string delim {","};
    string elf1 {};
    string elf2 {};
    int total {0};
    while (getline(file, line)) {
        elf1 = line.substr(0, line.find(delim));
        elf2 = line.substr(line.find(delim)+1);
        if (doesFullyContain(elf1, elf2)) {
            total++;
        }
    }
    cout << "Answer is: " << total << endl;
}