#include "Cannon.h"

Cannon::Cannon(int X, int Y, int Level) {
	setPosition(X, Y);
	setSpeed(Level * 1);
	setPower(Level * 1);
	setCost(5);
	setUpgrade(5);
	setSell(0.5 * Level * 5);
	level = Level;
}

void Cannon::setLevel(int Level) {
    level = Level;
	setSpeed(Level * 1);
	setPower(Level * 1);
	setSell(0.5 * Level * 5);
}


