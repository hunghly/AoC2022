#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

std::array<char, 52> priorities {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

char findCommon(string pack1, string pack2) {
    int found {};
    for (char ch : pack1) {
        found = pack2.find(ch);
        if (found != -1) {
            return ch;
        }
    }
    return (char) NULL;
}

int findPriority(char item) {
    for (int i = 0; i < priorities.size(); i++) {
        if (priorities[i] == item) {
            return i+1;
        }
    }
    return -1;
}

// AOC Day 3 Part 1
int main() {
  ifstream file{"input1.txt"};
  string line;
  string pack1;
  string pack2;
  char item;
  int sum {0};
  while (getline(file, line)) {
    pack1 = line.substr(0, line.size()/2);
    pack2 = line.substr(line.size()/2);
    item = findCommon(pack1, pack2);
    sum += findPriority(item);
  }
  cout << "Answer: " << sum << endl;
}