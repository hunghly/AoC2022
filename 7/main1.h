#ifndef _MAIN_H_
#define _MAIN_H_

#include <vector>
#include <string>

using namespace std;

struct File {
    string name;
    string size;
};

class Directory {
public:
    string name;
    Directory *parent;
    vector<File> files;
    Directory(string name) {
        this->name = name;
    }
    Directory(string name, Directory *parent) {
        this->name = name;
        this->parent = parent;
    }
    bool operator==(const Directory &rhs) const { return this->name == rhs.name;};
};



#endif