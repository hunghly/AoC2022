#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

using namespace std;

int rockPaperScissor(char opponent, char response) {
  if ((response =='X' && opponent == 'C')
          || (response == 'Y' && opponent == 'A')
          || (response == 'Z' && opponent == 'B')) { // win conditions: rock vs scissor, paper vs rock, scissors vs paper
    return 1;
  }
  else if ((response =='X' && opponent == 'B')
          || (response == 'Y' && opponent == 'C')
          || (response == 'Z' && opponent == 'A')) { // lose conditions: rock vs paper, paper vs scissors, scissors vs rock
    return -1;
  }
  else { // draw
    return 0;
  }
}

// return score based on game,
int calculateRound(char opponent, char response) {
  int score = 0;
  int result = rockPaperScissor(opponent, response);
  switch (response) {
  case 'X':
    score += 1;
    break;
  case 'Y':
    score += 2;
    break;
  case 'Z':
    score += 3;
    break;
  default:
    break;
  }
  if (result == 0) {
      score+=3;
  } else if (result == 1) {
    score+=6;
  }
  return score;
}

// AOC Day 2 Part 1
int main() {
  ifstream file{"input1.txt"};
  string line;
  char opponent{0};
  char response{0};
  int totalScore {0};
  while (getline(file, line)) {
    opponent = line[0];
    response = line[2];
    totalScore += calculateRound(opponent, response);
  }
  cout << "Answer: " << totalScore << endl;
}