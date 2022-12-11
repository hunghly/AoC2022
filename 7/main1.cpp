/** COMPILE WITH C++ 20
***/

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <list>
#include <memory>
#include "main1.h"

using namespace std;

list<Directory*> directories;
// string currentDirectory {};
Directory *currDirectoryPtr = NULL;
Directory emptyDir {""};

void printDirectory(Directory* directory, int distance) {
    for (int i = 0; i < directory->distanceFromRoot; i++) {
        cout << "\t";
    }
    cout << "(dir) " << directory->name << "(" << directory->dirFileSize << ")";
    // cout << "inside Print: directory: " << directory->name << " Size: " << directory->subdirectories.size() << endl;

    if (directory->subdirectories.size() > 0) {
        cout << "[" << directory->dirFileSize + directory->getSubDirFileSize() << "]";
    }
     cout << endl;

    if (directory->files.size() > 0) {
        for (auto f : directory->files) {
            for (int i = 0; i < directory->distanceFromRoot; i++) {
            cout << "\t";
            }
            cout << "\t(file) " << f.name << " (" << f.size << ")" << endl;
        }
    }
}

void printDirectories() {
    cout << "===Printing Dirs===" << endl;
    // list<Directory*> tmp = directories;
    for (auto &directory : directories) {
            // cout << "directory: " << directory->name << " Size: " << directory->subdirectories.size() << endl;

        // cout << "directory: " << directory->name << directory->subdirectories.size() << endl;
        if (directory->subdirectories.size() > 0) {
            // cout << "Printing subdirectories" << endl;
            // while (directory->subdirectories.size() > 0) {
            //     for (auto subdir : directory->subdirectories) {
            //         cout << "printing subdirs?" << endl;
            //         printDirectory(subdir, subdir->distanceFromRoot);
            //     }
            //     cout << "removing: " << (*directory->subdirectories.begin())->name << endl;
            //     directory->subdirectories.erase(directory->subdirectories.begin());
            // }
            printDirectory(directory, directory->distanceFromRoot);

        } else {
            // cout << "calling else " << endl;
            printDirectory(directory, directory->distanceFromRoot);
            // tmp.erase(tmp.begin());
        }

        


        // cout << "DFR: " << directory->name << directory->distanceFromRoot << endl;
        // for (int i = 0; i < directory->distanceFromRoot; i++) {
        //     cout << "\t";
        // }
        // cout << "(dir) " << directory->name << "(" << directory->dirFileSize << ")";
        // if (directory->subdirectories.size() > 0) {
        //     cout << "[" << directory->dirFileSize + directory->getSubDirFileSize() << "]";
        // }
        // cout << endl;

        // if (directory->files.size() > 0) {
        //     for (auto f : directory->files) {
        //         for (int i = 0; i < directory->distanceFromRoot; i++) {
        //         cout << "\t";
        //         }
        //         cout << "\t(file) " << f.name << " (" << f.size << ")" << endl;
        //     }
        // }
        // cout << endl;




        // if (directory->name != "root") {
        //     cout << "Parent: " << directory->parent->name << "| ";
        // }
        // if (directory->subdirectories.size() > 0) {
        //     cout << "Subdirectories: ";
        //     for (Directory* subdir : directory->subdirectories) {
        //         cout << subdir->name << ", ";
        //     }
        //     cout << "Subdir total filesize: " << directory->getSubDirFileSize() << "| ";
        // }
        // if (directory->files.size() > 0) {
        //     cout << "Files: ";
        //     for (File file : directory->files) {
        //         cout << file.name << "[" << file.size << "]" << ", ";
        //     }
        //     cout << "| Directory File Size: " << directory->dirFileSize;
        // }
        // cout << " Total File Size: " << directory->getSubDirFileSize() + directory->dirFileSize;
        // cout << endl;
        // cout << "Directory name: " << directory->name << "| ";
        // if (directory->name != "root") {
        //     cout << "Parent: " << directory->parent->name << "| ";
        // }
        // if (directory->subdirectories.size() > 0) {
        //     cout << "Subdirectories: ";
        //     for (Directory* subdir : directory->subdirectories) {
        //         cout << subdir->name << ", ";
        //     }
        //     cout << "Subdir total filesize: " << directory->getSubDirFileSize() << "| ";
        // }
        // if (directory->files.size() > 0) {
        //     cout << "Files: ";
        //     for (File file : directory->files) {
        //         cout << file.name << "[" << file.size << "]" << ", ";
        //     }
        //     cout << "| Directory File Size: " << directory->dirFileSize;
        // }
        // cout << " Total File Size: " << directory->getSubDirFileSize() + directory->dirFileSize;
        // cout << endl;
    }
}


Directory* getDirectory(string name) {
    for (auto &directory : directories) {
        if (directory->name == name) {
            // cout << "Directory exists:" << name << endl;
            return directory;
        }
    }
    return &emptyDir;
}

void runCD(vector<string> command) {
    if (command[2] == "/") {
        if (directories.size() == 0) {
            // create root directory
            directories.push_back(new Directory {"root", NULL});
        }
        currDirectoryPtr = getDirectory("root");
    }
    else if (command[2] == "..") {
        // change directory up one level
        currDirectoryPtr = currDirectoryPtr->parent;
        cout << "went up one level to: " << currDirectoryPtr->name << endl;
    }
    else {
        // if directory doesn't exist in list, add it
        if (getDirectory(command[2]) == &emptyDir) {
            // cout << "Creating new directory!" << endl;
            Directory *parent = getDirectory(currDirectoryPtr->name);
            directories.push_back(new Directory {command[2], parent});
            currDirectoryPtr = getDirectory(command[2]);
        } 
        // just change directory
        else {
            // cout << "Changing to directory: " << command[2] << endl;
            currDirectoryPtr = getDirectory(command[2]);
        }
    }
}

void printCommand(vector<string> command) {
    cout << "CMD: " << command[1];
    // Only print args if it has args
    if (command.size() == 3) {
        cout << " | ARGS: " << command[2];
    }
    cout << endl;
}

// Get the data that follows an ls command
vector<string> getLSData(ifstream &file) {
    // cout << "Getting LS data." << endl;
    vector<string> data {};
    string line;
    while (getline(file, line)) {
        data.push_back(line);
        // Check if the next line contains a command.
        if ((char) file.peek() == '$')
            return data;
    }
    return data;
}

// parse the ls data
void parseLSData(vector<string> data) {
    // cout << "Parsing LS Data for Current Directory:" << currDirectoryPtr->name << endl;
    for (string line : data) {
        // two conditions: 1. listing directory 2. listing file details

        // Condition 1
        if (line.substr(0, line.find(" ")) == "dir") {
            string directoryName = line.substr(line.find(" ")+1);
            if (getDirectory(directoryName) == &emptyDir) {
                // cout << "Found a new directory using LS! Current directory: " << currDirectoryPtr->name << endl;
                // Directory* newDir = new Directory(directoryName, currDirectoryPtr);
                directories.push_back(new Directory(directoryName, currDirectoryPtr));
                currDirectoryPtr->subdirectories.push_back(directories.back());


                // Directory *parent = getDirectory(currDirectoryPtr->name);
                // cout << parent->name << endl;
                // parent->subdirectories->push_back(directoryName);
                // parent->subdirectories.
            }
        }
        // Condition 2
        else {
            // int fileSize = stoi(line.substr(0, line.find(" ")));
            // string filename = line.substr(line.find(" ") + 1);
            // cout << "file size:" << fileSize << " filename:" << filename << endl;
            File newFile;
            newFile.size = stoi(line.substr(0, line.find(" ")));
            newFile.name = line.substr(line.find(" ") + 1);
            currDirectoryPtr->files.push_back(newFile);
            currDirectoryPtr->updateDirFileSize();
        }
    }
}

// int getRecursiveFileSize(Directory* d, int sum) {
//     cout << "sum is: " << sum << endl;

//     // lowest level dir
//     if (d->dirFileSize == 0 || d->parent == NULL) {
//         return sum;
//     }
//     sum += d->dirFileSize;
//     // else if it's not, then get the current filesize + parents
//     return getRecursiveFileSize(d->parent, sum);
// }

int findDirectoriesSum(int maxSize) {
    int sum = 0;
    vector<Directory> foundDirectories {};
    for (Directory* d : directories) {
        if ((d->dirFileSize + d->getSubDirFileSize()) < maxSize) {
            cout << "Checking directory: " << d->name << " Total Size:" <<  d->dirFileSize + d->getSubDirFileSize() << endl;
            sum+= (d->dirFileSize +  d->getSubDirFileSize());
            
        }
    }
    return sum;
}



//AOC Day 7 Part 1
int main() {
    ifstream file {"input1.txt"};
    string line;
    Directory root {"root"};
    string token {};
    vector<string> command {};
    vector<string> lsData {};
    int directorySum {};
    while (getline(file, line)) {
        cout << "Running:" << line << endl;
        // Perform command
        if(line[0] == '$') {
            stringstream ss(line);
            while(getline(ss, token, ' ')) {
                if (token != "\0") {
                    command.push_back(token);
                }
            }
            if (command[1] == "cd") {
                runCD(command);
            } else if (command[1] == "ls") {
                // get lines until next command detected
                lsData = getLSData(file);
                parseLSData(lsData);
                lsData.clear();
            }
            // clear command after running
            if (!command.empty()) {
                // cout << "Clearing" << endl;
                command.clear();
            }
            printDirectories();
        };
    }
    
    directorySum =  findDirectoriesSum(100000);
    cout << "Answer: " << directorySum << endl;
    // Delete pointers
    // for (auto &dir : directories) {
        // delete dir->subdirectories;
        // delete dir.parent;
    // }
}