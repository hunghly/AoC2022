#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

std::array<char, 52> priorities{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int findPriority(char item) {
  for (int i = 0; i < priorities.size(); i++) {
    if (priorities[i] == item) {
      return i + 1;
    }
  }
  return -1;
}

void printLines(vector<string> lines) {
  for (auto line : lines) {
    cout << line << " ";
  }
  cout << endl;
}

char findCommon(vector<string> lines) {
  int found{0};
  for (char ch : lines[0]) {
    found = 0;
    for (int i = 0; i < lines.size(); i++) {
      if (lines[i].find(ch) != -1) {
        found++;
      }
    }
    if (found == 3) {
      return ch;
    }
  }
  return (char)NULL;
}

// AOC Day 3 Part 2
int main() {
  ifstream file{"input1.txt"};
  vector<string> lines{};
  string line;
  string pack1;
  string pack2;
  char item;
  int sum{0};
  while (getline(file, line)) {

    if (lines.size() < 3) {
      // get lines
      lines.push_back(line);
    }
    if (lines.size() == 3) {
      // do processing on lines in vector
      item = findCommon(lines);
      sum += findPriority(item);
      lines.clear();
    }
  }
  cout << "Answer: " << sum << endl;
}