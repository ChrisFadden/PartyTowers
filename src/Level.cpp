#include "Level.h"
#include <utility>
#include <iostream>

#include "Path.h"

Level::Level(int h, int w) {
  height = h;
  width = w;
}

Level::~Level() {}

void Level::addGameObject(GameObject* gobj) {

    std::cout << "addGameObject called\n";
    int x = gobj->getX();
    int y = gobj->getY();

    // Is object within map? May need to change values.
    if (x > width || y > height || x < 0 || y < 0) {
        std::cout << "FAILED WITHIN MAP CHECK!!!\n";
        std::cout << x << " " << y << "\n";
        return;
    }

    std::pair<int, int> gobj_pos(x, y);

    if (occupied_tiles.find(gobj_pos) == occupied_tiles.end()) {
        std::cout << "Position is open!!!!!!!!!!!!!!\n";
        occupied_tiles.insert(gobj_pos);
        drawables.insert(gobj);
    } else {
        std::cout << "(" << gobj_pos.first << "," << gobj_pos.second
                << ") position already has an object\n";
    }
}

void Level::addPath(Path* path) {
    paths.push_back(path);
}

Path* Level::getPath(int id) {
    return paths.at(id);
}

int Level::getNumPaths() {
    return paths.size();
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
        std::cout << "OUT OF BOUNDS!!!\n";
        return;
    }

    std::cout << "new pos: " << x+dx << " " << y+dy << "\n";

    c->setX(x+dx);
    c->setY(y+dy);
}

bool Level::spotOpen(int x, int y) {
    return (occupied_tiles.find(std::pair<int,int>(x,y)) == occupied_tiles.end());
}
