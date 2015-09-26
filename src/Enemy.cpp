#include "Enemy.h"
#include "Level.h"
#include <utility>
#include <iostream>

using namespace std;

void Enemy::setSpeed(int Speed) { speed = Speed; }

int Enemy::getSpeed() { return speed; }

void Enemy::setHealth(int Health) { health = Health; }

int Enemy::getHealth() { return health; }

void Enemy::setAlive(bool IsAlive) { isAlive = IsAlive; }

bool Enemy::getAlive() { return isAlive; }

void Enemy::setMoney(int Money) { money = Money;}

int Enemy::getMoney() {
    return money;
}

void Enemy::setPosition(int X, int Y) {
	x = X;
	y = Y;
}

void Enemy::setPosition(pair<int, int> pos) {
    setPosition(pos.first, pos.second);
}

pair<int, int> Enemy::getPosition() {
	pair<int, int> position;
	position.first = x;
	position.second = y;
	return position;
}

bool Enemy::move() {
    if (pathInd >= path->length()) {
        return true;
    }
    if (pathInd == 0) {
        setPosition(path->getDest(pathInd));
        pathInd += 1;
    } else {
        pair<int, int> newPos = path->getDest(pathInd);
        if (x < newPos.first) {
            x += 1;
        } else if (x > newPos.first) {
            x -= 1;
        } else if (y < newPos.second) {
            y += 1;
        } else if (y > newPos.second) {
            y -= 1;
        } else {
            pathInd += 1;
        }
    }
    return false;
}

void Enemy::setPath(Path* path) {
    this->path = path;
    pathInd = 0;
}
