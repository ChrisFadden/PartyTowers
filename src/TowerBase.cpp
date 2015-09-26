#include "TowerBase.h"

TowerBase::TowerBase(int Health, bool IsAlive, int Wave) {
	health = Health;
	isAlive = IsAlive;
	wave = Wave;
}


void TowerBase::setHealth(int Health) {
	health = Health;
}

int TowerBase::getHealth() {
	return health;
}


void TowerBase::setAlive(bool IsAlive) {
	isAlive = IsAlive;
}

bool TowerBase::getAlive() {
	return isAlive;
}


void TowerBase::setWave(int Wave) {
	wave = Wave;
}

int TowerBase::getWave() {
	return wave;
}


