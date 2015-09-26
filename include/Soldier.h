#ifndef _SOLDIER_H
#define _SOLDIER_H
#include "Enemy.h"

class Soldier : public Enemy {
	public: 
		Soldier(int, int, int);
		void setWave(int);
		void loadImg(SDL_Renderer*);
};
#endif
