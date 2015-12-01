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
	
	bool isFiring;	// are we trying to shoot a bullet?

	void update()
	{
		xpos += xvel * sfw::getDeltaTime();

		xvel = 0;
		
		if (sfw::getKey(KEY_LEFT) && xvel == 0)		xvel = -400; // left
		if (sfw::getKey(KEY_RIGHT) && xvel == 0)	xvel = 400; // right

		if (sfw::getKey(KEY_SPACE) && !isFiring)
		{
			isFiring = true;

			// control how quickly the firing occurs
			bool success = false;
			// Some way to create the bullet
			for (int i = 0; i < bullets->size(); ++i)
				if (!bullets->at(i).alive)
				{
					bullets->at(i) = { xpos, ypos, 1000, .6f, true };
					success = true;
				}
			if (!success)
				bullets->push_back({xpos, ypos, 1000, .6f, true});
		}

		// if we're not pressing it, reset isFiring to false
		if (!sfw::getKey(KEY_SPACE) && isFiring)
		{
			isFiring = false;
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