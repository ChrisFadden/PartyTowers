#include <iostream>
#include <stdlib.h>
#include "Bullet.h"
#include "Enemy.h"

using namespace std;

Bullet::Bullet(Enemy* target, int power) {
    this->target = target;
    this->power = power;
}

int Bullet::getPower() {
    return power;
}

Enemy* Bullet::getTarget() {
    return target;
}

bool Bullet::move() {
    pair<int,int> targ = target->getPosition();
    if (abs(x - targ.first) < 3 && abs(y - targ.second) < 3) {
        return true;
    }
    if (x < targ.first) {
        x += 2;
    }
    if (x > targ.first) {
        x -= 2;
    }
    if (y < targ.second) {
        y += 2;
    }
    if (y > targ.second) {
        y -= 2;
    }
    return false;
}

void Bullet::movePosition(int dx, int dy) {
    x += dx;
    y += dy;
    setPosition(x,y);
}

void Bullet::setPosition(pair<int,int> pos) {
    setPosition(pos.first, pos.second);
}

void Bullet::setPosition(int X, int Y) {
    x = X;
    y = Y;
    setPos(x,y);
}

void Bullet::loadImg(SDL_Renderer* r) {
    GameObject::loadImg("./res/Rocket.png", r);
}
