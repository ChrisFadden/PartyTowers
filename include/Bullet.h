#ifndef _BULLET_H
#define _BULLET_H
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Bullet : public GameObject {

    public:
        Bullet(Player*, Enemy*, int);
        bool move();
        void movePosition(int, int);
        void setPosition(int, int);
        void setPosition(pair<int, int>);
        int getPower();
        bool getDead();
        void setDead(bool);
        Enemy* getTarget();
        Player* getSource();
        void loadImg(SDL_Renderer* r, int);
        SDL_Texture* getTexture();

    private:
        int power;
        Enemy* target;
        bool dead;
        Player* source;

};

#endif
