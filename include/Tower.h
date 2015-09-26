#ifndef _TOWER_H
#define _TOWER_H
#include <utility>
#include "GameObject.h"
class Tower : public GameObject {
 public:
  
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


  void setPosition(int, int);
  std::pair<int, int> getPosition();


  int level;
 private:
  int x;
  int y;
  int range;
  int power;
  int speed;
  int cost;
  int upgradeCost;
  int sellValue;
  
};
#endif
