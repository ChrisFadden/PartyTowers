#include "Rocket.h"

Rocket::Rocket(int X, int Y, int Level) {
	setPosition(X, Y);
	setSpeed(Level * 1.5);
	setPower(Level * 1.5);
	setCost(10);
	setUpgrade(10);
	setSell(0.666 * Level * 10);
	level = Level;
}

void Rocket::setLevel(int Level) {
    level = Level;
	setSpeed(Level * 1.5);
	setPower(Level * 1.5);
	setSell(0.666 * Level * 10);
}


