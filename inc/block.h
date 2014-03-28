#ifndef BLOCK_H
#define BLOCK_H

#include "sprite.h"

class Block : public Sprite{
	public:
		Block(float posX, float posY);
		~Block();

	private:
		void loadTextureRects();
};

#endif
