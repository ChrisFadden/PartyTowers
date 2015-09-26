#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Cursor.h"
#include <set>
#include <utility>

class Level {
 public:
  int height, width;
  Level(int h, int w);
  ~Level();
  void addGameObject(GameObject* gobj);
  void removeGameObject(GameObject* gobj);
  void moveGameObject(GameObject* gobj, int, int);
  void moveCursor(Cursor* c, int, int);
  bool spotOpen(int x, int y);

 private:
  std::set<std::pair<int, int>> occupied_tiles;
  std::set<GameObject*> drawables;
  std::set<std::pair<int, int>> EnemyPath;
};

#endif
