#ifndef _TOWERBASE_H
#define _TOWERBASE_H
#include "GameObject.h"

class TowerBase : public GameObject {
	public:
		TowerBase(int, bool, int); //Default Constructor
	
		void setHealth(int); //Function for setting enemny health
		int getHealth(); //Function for getting enemy health
	
		void setAlive(bool); //Function for setting enemy life status
		bool getAlive(); //Function for getting enemy life status
		
		void setWave(int); //Function for setting level of enemy
		int getWave(); //Function for getting level of enemy
	private:
		int health;
		bool isAlive;
		int wave;
};
#endif
