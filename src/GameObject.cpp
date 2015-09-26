#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() {}

int GameObject::getX() { return x; }

int GameObject::getY() { return y; }

void GameObject::setX(int nx) { x = nx; }

void GameObject::setY(int ny) { y = ny; }

void GameObject::setPos(int nx, int ny) {
  x = nx;
  y = ny;
}
