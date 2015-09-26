#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Cursor.h"
#include "Level.h"
#include <utility>

using namespace std;

class Player {
 private:
  int playerID;
  int score;
  int money;
  string name;
  Cursor* cursor;
  Level* lvl;

 public:
  Player(int, int, int, Level*);  // Constructor
  int getPlayerID();  // Function to get player ID
  void setScore(int);  // Function to set Score
  int getScore();  // Function to get score
  void setMoney(int);  // Function to set money
  int getMoney();  // Function to get money
  void addMoney(int);
  void setName(string);
  string getName(); 
  //User input  
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();


  //other
  std::pair<int,int> getPos();
  void loadImg(SDL_Renderer* r);
  SDL_Texture* getTexture();

};
#endif
