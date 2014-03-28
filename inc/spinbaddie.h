#ifndef SPINBADDIE_H
#define SPINBADDIE_H

#include "enemy.h"

class SpinBaddie : public Enemy{
	public:
		SpinBaddie(float x, float y, int lvl);
		~SpinBaddie();

	private:
		void loadTextureRects();
};

#endif
