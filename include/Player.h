#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>

using namespace std;

class Player {
 private:
  string playerID;
  int score;
  int money;

 public:
  Player(string, int, int);  // Constructor
  string getPlayerID();  // Function to get player ID
  void setScore(int);  // Function to set Score
  int getScore();  // Function to get score
  void setMoney(int);  // Function to set money
  int getMoney();  // Function to get money
};
#endif
