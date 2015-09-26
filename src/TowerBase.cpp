#include "TowerBase.h"

TowerBase::TowerBase(bool IsAlive, int Wave) {
  health = 100;
  isAlive = IsAlive;
  wave = Wave;
}

void TowerBase::setHealth(int Health) { health = Health; }

int TowerBase::getHealth() { return health; }

void TowerBase::setAlive(bool IsAlive) { isAlive = IsAlive; }

bool TowerBase::getAlive() { return isAlive; }

void TowerBase::setWave(int Wave) { 
	wave = Wave;
	if (wave % 5) {
		setHealth((health + 20));
	}
}

void TowerBase::loadImg(SDL_Renderer* r) {
	std::string s = "./res/TowerBase.png";
	GameObject::loadImg(s, r);
}
