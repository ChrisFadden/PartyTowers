#ifndef _TOWER_H
#define _TOWER_H
#include <utility>
#include "GameObject.h"
#include "Tower.h"
#include "Player.h"

class Tower : public GameObject {
 public:
 
  Tower();

  void setRange(int);  // Set function for range
  int getRange();  // Get function for range

  void setPower(int); // Set function for power
  int getPower();  // Get function for power
  
  void setSpeed(int); // Set function for speed
  int getSpeed();  // Get function for speed

  void setCost(int);
  int getCost();  // Get function for cost

  void setUpgrade(int);
  int getUpgrade();  // Get function for upgradeCost

  void setSell(int);
  int getSell();  // Get function for sellValue

  void setTimeout(int);
  void reloadTower();
  bool canFire();
  void update();

  void setPosition(int, int);
  std::pair<int, int> getPosition();

  void setPlayer(Player* pin);
  Player* getPlayer();
  int level;
  virtual int getType();
 private:
  int x;
  int y;
  int range;
  int power;
  int speed;
  int cost;
  int upgradeCost;
  int sellValue;
  int timeout;
  int reload;
  Player* p;
   
};
#endif
