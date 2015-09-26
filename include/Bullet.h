#ifndef _BULLET_H
#define _BULLET_H
#include "GameObject.h"
#include "Enemy.h"

class Bullet : public GameObject {

    public:
        Bullet(Enemy*, int);
        bool move();
        void movePosition(int, int);
        void setPosition(int, int);
        void setPosition(pair<int, int>);
        int getPower();
        Enemy* getTarget();
        void loadImg(SDL_Renderer* r);
        SDL_Texture* getTexture();

    private:
        int power;
        Enemy* target;

};

#endif
