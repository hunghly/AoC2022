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
#include <list>
#include "main1.h"

using namespace std;

list<Directory> directories {};
string currentDirectory {};
Directory emptyDir {""};

bool isACommand(string line) {
    // Check if command or std output
    if (line[0] == '$') {
        cout << "Parsing command:" << line << endl;
        return true;
    }
    return false;
}

void printDirectories() {
    for (auto directory : directories) {
        cout << "Directory name: " << directory.name << endl;
        if (directory.name != "root") {
            cout << "Directory parent: " << directory.parent->name << endl;
        }
    }
}

Directory& getDirectory(string name) {
    for (auto &directory : directories) {
        if (directory.name == name) {
            cout << "Directory exists:" << name << endl;
            return directory;
        }
    }
    return emptyDir;
}

void runCD(vector<string> command) {
    // if (command[1] == "cd") {
        if (command[2] == "/") {
            if (directories.size() == 0) {
                // create root directory
                directories.push_back(Directory {"root", NULL});
            }
            currentDirectory = "root";
        }
        else if (command[2] == "..") {
            // implement this
        }
        else {
            // if directory doesn't exist in list, add it
            if (getDirectory(command[2]) == emptyDir) {
                cout << "Creating new directory!" << endl;
                Directory *parent = &getDirectory(currentDirectory);
                directories.push_back(Directory {command[2], parent});
                currentDirectory = command[2];
            } 
            // just change directory
            else {
                currentDirectory = command[2];
            }
        }     
    // }
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
            if (command[1] == "cd") {
                runCD(command);
            } else if (command[1] == "ls") {
                // get lines until next command detected
            }
            printDirectories();
            // clear command after running
            if (!command.empty()) {
                // cout << "Clearing" << endl;
                command.clear();
            }
        };
    }
}