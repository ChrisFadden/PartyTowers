#include "Cavalry.h"
#include <math.h>

Cavalry::Cavalry(int Wave, int X, int Y) {
	setPosition(X, Y);
	setHealth(M_PI + (Wave / 2));
	setSpeed( 1 + (Wave / 2));
	setAlive(true);
	wave = Wave;
}

void Cavalry::setWave(int Wave) {
	wave = Wave;
	setHealth(M_PI + (Wave / 2));
	setSpeed(1 + (Wave / 2));
}

