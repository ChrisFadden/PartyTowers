#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "DrawableObject.h"
#include <string>

class GameObject {
 protected:
  int x, y;
  DrawableObject* drawable;

 public:
  GameObject();
  ~GameObject();
  int getX();
  int getY();
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setPos(int nx, int ny);
  virtual void draw();
  void loadImg(std::string fn, SDL_Renderer* r);
};

#endif
