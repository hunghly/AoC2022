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

bool verifyDuplicates(string buffer) {
    set<char> s {0};
    for (char ch : buffer) {
        if (s.contains(ch)) {
            return false;
        }
        s.insert(ch);
    }
    return true;
}

void processStream(string line) {
    int counter {0};
    string buffer;
    for (char ch : line) {
        buffer += ch;
        counter++;
        // every four characters, perform a check
        if (buffer.size() == 4) {
            // If no duplicates, then it's the start of the packet
            if (verifyDuplicates(buffer)) {
                cout << "Answer: " << counter << endl;
            } else {
                // remove the first character
                buffer.erase(0,1);
            }
        }
    }

}


//AOC Day 6 Part 2
int main() {
    ifstream file {"input1.txt"};
    string line;
    while (getline(file, line)) {
        processStream(line);
    }
}