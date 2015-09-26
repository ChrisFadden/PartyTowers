#include "Level.h"
#include <utility>
#include <iostream>

Level::Level(int h, int w) {
  height = h;
  width = w;
}

Level::~Level() {}

void Level::addGameObject(GameObject* gobj) {
  int x = gobj->getX();
  int y = gobj->getY();

  // Is object within map? May need to change values.
  if ((x > width || y > height) && x >= 0 && y >= 0) {
    return;
  }

  std::pair<int, int> gobj_pos(x, y);

  if (occupied_tiles.find(gobj_pos) == occupied_tiles.end()) {
    occupied_tiles.insert(gobj_pos);
    drawables.insert(gobj);
  } else {
    std::cout << "(" << gobj_pos.first << "," << gobj_pos.second
              << ") position already has an object\n";
  }
}

void Level::removeGameObject(GameObject* gobj) {
  int x = gobj->getX();
  int y = gobj->getY();

  std::pair<int, int> gobj_pos(x, y);
  auto it = occupied_tiles.find(gobj_pos);
  if (it != occupied_tiles.end()) {
    occupied_tiles.erase(it);
    drawables.erase(drawables.find(gobj));
  } else {
    std::cout << "(" << gobj_pos.first << "," << gobj_pos.second
              << ") position doesn't have an object\n";
  }
}

void Level::moveGameObject(GameObject* gobj, int addX, int addY) {
  int x = gobj->getX();
  int y = gobj->getY();

  x += addX;
  y += addY;

  // Is object out of bounds
  if (x > width || y > height || x < 0 || y < 0) {
    removeGameObject(gobj);
    std::cout << "Incremented index out of bounds...  Destroyed Object"
              << std::endl;
    return;
  }

  gobj->setX(x);
  gobj->setY(y);
  return;
}

void Level::moveCursor(Cursor* c, int dx, int dy) {
    int x = c->getX();
    int y = c->getY();
    
    //If out of bounds, don't move cursor
    if (x+dx > width || y+dy > height) {
        return;
    }

    c->setX(x+dx);
    c->setY(y+dy);
}
