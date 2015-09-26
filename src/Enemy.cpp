#include "Enemy.h"

Enemy::Enemy(int Speed, int Health, bool IsAlive, int Wave) {
  speed = Speed;
  health = Health;
  isAlive = IsAlive;
  wave = Wave;
}

void Enemy::setSpeed(int Speed) { speed = Speed; }

int Enemy::getSpeed() { return speed; }

void Enemy::setHealth(int Health) { health = Health; }

int Enemy::getHealth() { return health; }

void Enemy::setAlive(bool IsAlive) { isAlive = IsAlive; }

bool Enemy::getAlive() { return isAlive; }

void Enemy::setWave(int Wave) { wave = Wave; }

int Enemy::getWave() { return wave; }
