

#ifndef _TOWER_H
#define _FIELD_H

#include <iostream>
#include "GameObject.h"
class Tower : public GameObject
{
  public:
    Tower(); //Default Constructor
    Tower(int, int); //Tower with a specific location
    Tower(int, int, int); //Tower with a specific location and range
    Tower(int, int, int, int); //Tower with specific location, range, and power  
    void SetRange(int); //Set function for range
    int GetRange(); //Get function for range

    void SetPower(int); //Set function for power
    int GetPower(); //Get function for power 
  private:
    int range;
    int power;
}
#endif
