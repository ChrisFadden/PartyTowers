#ifndef _ROCKET_H
#define _ROCKET_H
#include "Tower.h"

class Rocket : public Tower {
	public:
		Rocket(int, int, int);
		void setLevel(int);
        int getLevel();
		void loadImg(SDL_Renderer*);
                int getType();
};
#endif
