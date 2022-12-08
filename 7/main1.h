#ifndef _MAIN_H_
#define _MAIN_H_

#include <ratio>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct File {
    string name;
    int size;
};

class Directory {
public:
    string name;
    Directory *parent;
    vector<Directory*> subdirectories;
    vector<File> files;
    int distanceFromRoot = 0;
    int dirFileSize = 0;
    

    Directory(string name) {
        this->name = name;
    }
    Directory(string name, Directory *parent) {
        this->name = name;
        this->parent = parent;
        // this->subdirectories = NULL;
        if (this->parent != NULL) {
            Directory* tmp = parent;
            int distance = 1;
            while (tmp->parent != NULL) {
                cout << "finding distance: " << tmp->parent->name;
                distance++;
                tmp = tmp->parent;
            }
            cout << "Distance from Root: " << distance << endl;
            distanceFromRoot = distance;
        }
        // if (tmp->parent != NULL) {
        //     cout << "finding distance: " << tmp.parent->name;
        //     tmp = *tmp.parent;
        // }
    }
    Directory(string name, Directory *parent, vector<Directory*> subdirectories) {
        this->name = name;
        this->parent = parent;
        this->subdirectories = subdirectories;
    }
    ~Directory() {
        cout << "inside deconstructor" << endl;
    }
    bool operator==(const Directory &rhs) const { return this->name == rhs.name;};
    
    void updateDirFileSize() {
        int sum = 0;
        for (File f : files) {
            sum += f.size;
        }
        dirFileSize = sum;
    }

    int getSubDirFileSize() {
        int sum = 0;
        for (Directory* d : subdirectories) {
            sum += d->dirFileSize;
        }
        return sum;
    }
};



#endif