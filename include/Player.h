#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Cursor.h"
#include "Level.h"

using namespace std;

class Player {
 private:
  int playerID;
  int score;
  int money;
  Cursor* cursor;
  Level* lvl;

 public:
  Player(int, int, int, Level*);  // Constructor
  int getPlayerID();  // Function to get player ID
  void setScore(int);  // Function to set Score
  int getScore();  // Function to get score
  void setMoney(int);  // Function to set money
  int getMoney();  // Function to get money
  
  //User input  
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

};
#endif
