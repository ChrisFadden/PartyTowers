#include "Cavalry.h"
#include <math.h>

Cavalry::Cavalry(int Wave, int X, int Y) {
	setPosition(X, Y);
	setHealth(M_PI + (Wave / 1.5));
	setSpeed( 1 + (Wave / 1.5));
	setAlive(true);
	setPower(1 + (Wave / 1.5));
	setMoney(66 + (Wave / 1.5));
	wave = Wave;
}

void Cavalry::setWave(int Wave) {
	wave = Wave;
	setHealth(M_PI + (Wave / 1.5));
	setSpeed(1 + (Wave / 1.5));
	setMoney(66 + (Wave / 1.5));
	setPower(1 + (Wave / 1.5));
}

void Cavalry::loadImg(SDL_Renderer* r) {
    if(isAlive){
        GameObject::loadImg("./res/Cavalry.png", r);
    } else{
        GameObject::loadImg("./res/Explosion.png", r);
    }
}
