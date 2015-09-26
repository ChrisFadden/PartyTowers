#include "Enemy.h"
#include "Level.h"

using namespace std;

void Enemy::setSpeed(int Speed) { speed = Speed; }

int Enemy::getSpeed() { return speed; }

void Enemy::setHealth(int Health) { health = Health; }

int Enemy::getHealth() { return health; }

void Enemy::setAlive(bool IsAlive) { isAlive = IsAlive; }

bool Enemy::getAlive() { return isAlive; }

void Enemy::setPosition(int X, int Y) {
	x = X;
	y = Y;
}

pair<int, int> Enemy::getPosition() {
	pair<int, int> position;
	position.first = x;
	position.second =y;
	return position;
}


