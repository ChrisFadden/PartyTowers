#include <iostream>
#include "Tower.h"

/********************
 * Constructors
 *******************/
// Default Constructor, with usuable values
Tower::Tower() {
  range = 5;
  power = 1;
  isAlive = true;
}

// Constructor with Location
Tower::Tower(int i, int j) {
  x = i;
  y = j;
}

// Constructor with Location and Range
Tower::Tower(int i, int j, int r) {
  x = i;
  y = j;
  range = r;
}

// Constructor with Location, Range, and Power
Tower::Tower(int i, int j, int r, int p) {
  x = i;
  y = j;
  range = r;
  power = p;
}

/***********************
 * Get and Set Functions
 **********************/
void Tower::SetRange(int r) { range = r; }

int Tower::GetRange() { return range; }

void Tower::SetPower(int p) { power = p; }

int Tower::GetPower() { return power; }

bool Tower::GetAlive() { return isAlive; }

void Tower::SetAlive(bool alive) { isAlive = alive; }
