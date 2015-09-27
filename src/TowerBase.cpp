#include "TowerBase.h"
using namespace std;

TowerBase::TowerBase( int Wave) {
  health = 100;
  isAlive = true;;
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

void TowerBase::setPosition(int X, int Y) {
	x = X;
	y = Y;
}

void TowerBase::setPosition(pair<int, int> pos) {
	setPosition(pos.first, pos.second);
}

pair<int, int> TowerBase::getPosition() {
	pair<int, int> pos;
	pos.first = x;
	pos.second = y;
	return pos;
}




void TowerBase::loadImg(SDL_Renderer* r) {
	std::string s = "./res/TowerBase.png";
	GameObject::loadImg(s, r);
}
