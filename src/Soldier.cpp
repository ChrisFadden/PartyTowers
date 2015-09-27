#include "Soldier.h"
#include <math.h>

Soldier::Soldier(int Wave, int X, int Y) {
	setPosition(X, Y);
	setHealth(M_PI + (Wave / 2));
	setSpeed( 1 + (Wave / 2));
	setPower(5 + (Wave / 2));
	setAlive(true);
	setMoney(50 + (Wave / 2));
	wave = Wave;
}

void Soldier::setWave(int Wave) {
	wave = Wave;
	setHealth(M_PI + (Wave / 2));
	setSpeed(1 + (Wave / 2));
	setMoney(50 + (Wave / 2));
	setPower(5 + (Wave / 2));
}



void Soldier::loadImg(SDL_Renderer* r) {
    if (isAlive) {
        GameObject::loadImg("./res/Soldier.png", r);
    } else {
        GameObject::loadImg("./res/Explosion.png", r);
    }
}
