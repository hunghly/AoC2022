#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

using namespace std;

void printList(list<int> l) {
  for (auto item : l) {
    cout << item << " ";
  }
  cout << endl;
}

// AOC Day 1 Part 2
int main() {
  ifstream file{"input1.txt"};
  string line;
  int sum{0};
  list<int> maxCalories{};
  int minInList{0};
  while (getline(file, line)) {
    if (line == "") {
      // Compare calories
      if (sum > minInList) {
        if (maxCalories.size() == 3) {
          maxCalories.pop_front();
          maxCalories.push_back(sum);
          maxCalories.sort();
          minInList = maxCalories.front();
        } else {
          maxCalories.push_back(sum);
          maxCalories.sort();
          minInList = maxCalories.front();
        }
      }
      sum = 0;
      continue;
    }
    sum += stoi(line);
  }
  int total = accumulate(maxCalories.begin(), maxCalories.end(), 0);
  cout << "Answer is: " << total;
}