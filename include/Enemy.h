#ifndef _ENEMY_H
#define _ENEMY_H
#include "GameObject.h"
#include "Path.h"
#include <utility>
class Enemy : public GameObject {
 public:

  void setSpeed(int);  // Function for setting enemy speed
  int getSpeed();  // Function for getting enemy speed

  void setHealth(int);  // Function for setting enemny health
  int getHealth();  // Function for getting enemy health

  void setAlive(bool);  // Function for setting enemy life status
  bool getAlive();  // Function for getting enemy life status
	
  void setPosition(int, int);
  void setPosition(std::pair<int, int>);
  std::pair<int, int> getPosition();

  void setMoney(int);
  int getMoney();

  bool move();
  void setPath(Path*);
  
  virtual void setWave(int);
  int wave;
  
  void setPower(int);
  int getPower();

 protected:
  int power;
  int x;
  int y;
  int speed;
  int money;
  int health;
  bool isAlive;
  Path* path;
  int pathInd;
};
#endif
