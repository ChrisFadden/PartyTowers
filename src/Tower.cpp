#include <iostream>
#include "Tower.h"

using namespace std;
/***********************
 * Get and Set Functions
 **********************/
void Tower::setRange(int r) { range = r; }
int Tower::getRange() { return range; }

void Tower::setPower(int p) { power = p;}
int Tower::getPower() { return power; }

void Tower::setSpeed(int s) { speed = s; }
int Tower::getSpeed() { return speed; }

void Tower::setCost(int c) { cost = c; }
int Tower::getCost() { return cost; }

void Tower::setUpgrade(int u) { upgradeCost = u; }
int Tower::getUpgrade() { return upgradeCost; }

void Tower::setSell(int S) { sellValue = S; }
int Tower::getSell() { return sellValue; }

void Tower::setPosition(int X, int Y){
	x = X;
	y = Y;
}



pair<int, int> Tower::getPosition() { 
	pair<int, int > position; 
	position.first = x;
	position.second = y;
	return position;
}




