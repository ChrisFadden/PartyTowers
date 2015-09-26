#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include <set>
#include <utility>

class Level {

    public:
        int height, width;
        Level(int h, int w);
        ~Level();
        void addGameObject(GameObject* gobj);
        void removeGameObject(GameObject* gobj);
    private:
        std::set<std::pair<int,int>> occupied_tiles;
        std::set<GameObject*> drawables;
};

#endif
