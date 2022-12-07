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

class Directory {
public:
    string name;
    vector<Directory> directories;
    vector<string> files;
    Directory(string name) {
        this->name = name;
    }
};

bool isACommand(string line) {
    // Check if command or std output
    if (line[0] == '$') {
        cout << "Parsing command:" << line << endl;
        return true;
    }
    return false;
}

void printCommand(vector<string> command) {
    cout << "CMD: " << command[1];
    // Only print args if it has args
    if (command.size() == 3) {
        cout << " | ARGS: " << command[2];
    }
    cout << endl;
}

//AOC Day 7 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    Directory root {"root"};
    string currentDirectory {};
    string token {};
    vector<string> command {};
    while (getline(file, line)) {
        // Perform command
        if(isACommand(line)) {
            stringstream ss(line);
            while(getline(ss, token, ' ')) {
                if (token != "\0") {
                    // cout << "tok" << token << endl
                    command.push_back(token);
                }
            }
            printCommand(command);

            // clear command after running
            if (!command.empty()) {
                // cout << "Clearing" << endl;
                command.clear();
            }
        };
    }
}