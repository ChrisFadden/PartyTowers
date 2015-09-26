#ifndef _CAVALRY_H
#define _CAVALRY_H
#include "Enemy.h"

class Cavalry : public Enemy {
	public: 
		Cavalry(int, int, int);
		void setWave(int);
		void loadImg(SDL_Renderer*);
};
#endif
