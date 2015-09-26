#include "Soldier.h"
#include <math.h>

Soldier::Soldier(int Wave, int X, int Y) {
	setPosition(X, Y);
	setHealth(M_PI + (Wave / 2));
	setSpeed( 1 + (Wave / 2));
	setAlive(true);
	wave = Wave;
}

void Soldier::setWave(int Wave) {
	wave = Wave;
	setHealth(M_PI + (Wave / 2));
	setSpeed(1 + (Wave / 2));
}

