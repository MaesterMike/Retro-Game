#pragma once
#include "sfwdraw.h"

class Enemy
{
public:
	float x, y;			// position
	float w, h;			// dimensions (width and height)
	float xvel, yvel;	// velocity

	int textureId;		// texture id

	bool isAlive;		// is this enemy alive?

	void update()
	{
		x += xvel * sfw::getDeltaTime();
		y += yvel * sfw::getDeltaTime();

		if (y < -25)
		{
			y = 625;
		}
	}

	void draw()
	{
		sfw::drawTexture(textureId, x, y, w, h);
	}
};