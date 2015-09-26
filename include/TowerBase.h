#ifndef _TOWERBASE_H
#define _TOWERBASE_H
#include "GameObject.h"

class TowerBase : public GameObject {
 public:
  TowerBase(bool, int);  // Default Constructor

  void setHealth(int);  // Function for setting enemny health
  int getHealth();  // Function for getting enemy health

  void setAlive(bool);  // Function for setting enemy life status
  bool getAlive();  // Function for getting enemy life status

  void loadImg(SDL_Renderer*);
  void setWave(int);  // Function for setting level of enemy
 private:
  int health;
  bool isAlive;
  int wave;
};
#endif
