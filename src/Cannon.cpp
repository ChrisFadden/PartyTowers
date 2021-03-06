#include "Cannon.h"

Cannon::Cannon(int X, int Y, int Level) {
	setPosition(X, Y);
	setSpeed(Level * 1);
	setPower(Level * 1);
	setCost(50);
	setUpgrade(50 + ((50 * (Level-1))/ 2));
	setSell(0.5 * Level * 5);
    setRange(96);
    setTimeout(120);
	level = Level;
}

void Cannon::setLevel(int Level) {
    level = Level;
	setSpeed(Level * 1);
	setPower(Level * 1);
	setSell(0.5 * Level * 5);
	setUpgrade(50 + ((50 * (Level -1)) / 2));
}

void Cannon::loadImg(SDL_Renderer* r) {
	GameObject::loadImg("./res/Cannon.png", r);
}

int Cannon::getType(){
    return 0;
}

int Cannon::getLevel() {
    return level;
}
