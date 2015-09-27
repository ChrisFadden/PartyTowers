#ifndef _CANNON_H
#define _CANNON_H
#include "Tower.h"

class Cannon : public Tower {
	public:
		Cannon(int, int, int);
		void setLevel(int);
        int getLevel();
		void loadImg(SDL_Renderer*);
                int getType();
};
#endif
