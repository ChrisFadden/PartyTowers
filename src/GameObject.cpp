#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() {}

std::pair<int,int> GameObject::getPosition() { return std::pair<int,int>(x,y);}

int GameObject::getX() { return x; }

int GameObject::getY() { return y; }

void GameObject::setX(int nx) { x = nx; }

void GameObject::setY(int ny) { y = ny; }

void GameObject::setPos(int nx, int ny) {
  x = nx;
  y = ny;
}

SDL_Texture* GameObject::draw() {
    return drawable->getTexture();
}

void GameObject::loadImg(std::string fn, SDL_Renderer* r) {
    drawable = new DrawableObject(fn, r);
}
