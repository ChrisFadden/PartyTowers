#ifndef _TOWER_H
#define _TOWER_H

#include <iostream>
#include "GameObject.h"
class Tower : public GameObject {
 public:
  Tower();  // Default Constructor
  Tower(int, int);  // Tower with a specific location
  Tower(int, int, int);  // Tower with a specific location and range
  Tower(int, int, int, int);  // Tower with specific location, range, and power
  void SetRange(int);  // Set function for range
  int GetRange();  // Get function for range

  void SetPower(int);  // Set function for power
  int GetPower();  // Get function for power

  void SetAlive(bool);  // Set function for isAlive
  bool GetAlive();  // Get function for isAlive

  void SetSpeed(int);  // Set function for speed
  int GetSpeed();  // Get function for speed

  void SetCost(int);  // Set function for cost
  int GetCost();  // Get function for cost

  void SetUpgrade(int);  // Set function for upgradeCost
  int GetUpgrade();  // Get function for upgradeCost

  void SetSell(int);  // Set function for sellValue
  int GetSell();  // Get function for sellValue

  void SetLevel(int);  // Set function for level
  int GetLevel();  // Get function for level


 private:

  int range;
  int power;
  bool isAlive;
  int speed;
  int cost;
  int upgradeCost;
  int sellValue;
  int level;
  
};
#endif
