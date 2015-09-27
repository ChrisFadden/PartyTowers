#include "Rocket.h"

Rocket::Rocket(int X, int Y, int Level) {
	setPosition(X, Y);
	setSpeed(Level * 1.5);
	setPower(Level * 1.5);
	setCost(10);
	setUpgrade(10);
    setRange(128);
    setTimeout(180);
	setSell(0.666 * Level * 10);
	level = Level;
}

void Rocket::setLevel(int Level) {
    level = Level;
	setSpeed(Level * 1.5);
	setPower(Level * 1.5);
	setSell(0.666 * Level * 10);
}

void Rocket::loadImg(SDL_Renderer* r) {
	GameObject::loadImg("./res/RocketTower.png", r);
}

int Rocket::getType(){
    return 1;
}

