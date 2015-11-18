#pragma once
#include "sfwdraw.h"
#include <vector>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

struct bullet
{
	float xpos, ypos;
	float yvel;
	float lifetime;
	bool alive;

	void update()
	{
		lifetime -= sfw::getDeltaTime();
		alive = lifetime > 0;
		ypos += yvel * sfw::getDeltaTime();
	}
};

struct ship
{
	float xpos, ypos;
	float xvel;
	float xacc;
	float xspeed;
	float score;

	std::vector<bullet> *bullets;
	
	void update()
	{
		xpos += xvel * sfw::getDeltaTime();

		if (sfw::getKey(KEY_LEFT) && xvel == 0)
		{
			xvel = -1000;
			//xacc = 0;
		}
		else if (sfw::getKey(KEY_RIGHT) && xvel == 0)
		{
			xvel = 1000;
			//xacc = 0;
		}
		else
		{
			xvel = 0;
		}

		if (sfw::getKey(KEY_SPACE))
		{
			// control how quickly the firing occurs
			bool success = false;
			// Some way to create the bullet
			for (int i = 0; i < bullets->size(); ++i)
				if (!bullets->at(i).alive)
				{
					bullets->at(i) = { xpos, ypos, 1000, .6f, true };
					success = true;

				}
			if(!success)
				bullets->push_back({xpos, ypos, 1000, .6f, true});
		}


		if (xpos < 25)
		{
			xpos = 25;
			xvel = 0;
		}
		else if (xpos > SCREEN_WIDTH - 25)
		{
			xpos = SCREEN_WIDTH - 25;
			xvel = 0;
		}
	}
};