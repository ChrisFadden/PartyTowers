#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Path.h"
#include "Cursor.h"
#include <set>
#include <utility>
#include <vector>

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
  void addPath(Path*);
  Path* getPath(int);
  int getNumPaths();


 private:
  std::set<std::pair<int, int>> occupied_tiles;
  std::set<GameObject*> drawables;
  std::vector<Path*> paths;
};

#endif
