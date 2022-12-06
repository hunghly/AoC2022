#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

using namespace std;

string findLosingHand(char opponent) {
    switch (opponent) {
        case 'A':
            return "scissors";
        case 'B':
            return "rock";
        case 'C':
            return "paper";
        default:
            return NULL;
    }
}

string findWinningHand(char opponent) {
    switch (opponent) {
        case 'A':
            return "paper";
        case 'B':
            return "scissors";
        case 'C':
            return "rock";
        default:
            return NULL;
    }
}

string findDrawingHand(char opponent) {
    switch (opponent) {
        case 'A':
            return "rock";
        case 'B':
            return "paper";
        case 'C':
            return "scissors";
        default:
            return NULL;
    }
}

/*
int rockPaperScissor(char opponent, string response) {
  if ((response =="rock" && opponent == 'C')
          || (response == "paper" && opponent == 'A')
          || (response == "scissors" && opponent == 'B')) { // win conditions: rock vs scissor, paper vs rock, scissors vs paper
    return 1;
  }
  else if ((response =="rock" && opponent == 'B')
          || (response == "paper" && opponent == 'C')
          || (response == "scissors" && opponent == 'A')) { // lose conditions: rock vs paper, paper vs scissors, scissors vs rock
    return -1;
  }
  else { // draw
    return 0;
  }
}
*/

// return score based on game,
int calculateRound(char opponent, char selection) {
  int score = 0;
  string response {};
  switch (selection) {
  case 'X': // I want to Lose
    response = findLosingHand(opponent);
    break;
  case 'Y': // Draw
    response = findDrawingHand(opponent);
    score+=3;
    break;
  case 'Z': // I want to Win
    response = findWinningHand(opponent);
    score+=6;
    break;
  default:
    break;
  }
  // Add to score based on our new response
  if (response == "rock")
    score+=1;
  else if (response == "paper")
    score+=2;
  else if (response == "scissors")
    score+=3;
  return score;
}

// AOC Day 2 Part 2
int main() {
  ifstream file{"input1.txt"};
  string line;
  char opponent{0};
  char selection{0};
  int totalScore {0};
  while (getline(file, line)) {
    opponent = line[0];
    selection = line[2];
    totalScore += calculateRound(opponent, selection);
  }
  cout << "Answer: " << totalScore << endl;
}