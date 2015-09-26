#ifndef _ENEMY_H
#define _ENEMY_H
#include "GameObject.h"

class Enemy : public GameObject {
	public:
		Enemy(int, int, bool, int); //Default Constructor
	
		void setSpeed(int); //Function for setting enemy speed
		int getSpeed(); //Function for getting enemy speed
	
		void setHealth(int); //Function for setting enemny health
		int getHealth(); //Function for getting enemy health
	
		void setAlive(bool); //Function for setting enemy life status
		bool getAlive(); //Function for getting enemy life status
		
		void setWave(int); //Function for setting level of enemy
		int getWave(); //Function for getting level of enemy
	private:
		int speed;
		int health;
		bool isAlive;
		int wave;
};
#endif
