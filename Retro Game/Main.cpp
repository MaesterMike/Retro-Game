#include <iostream>
#include <cmath>
#include "Ship.h"
#include "sfwdraw.h"
#include "Enemy.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

bool checkCollision(bullet playerBullet, Enemy enemyShip)
{
	// check for collision
	float distance = sqrt(((enemyShip.x - playerBullet.xpos) * (enemyShip.x - playerBullet.xpos)) + ((enemyShip.y - playerBullet.ypos) * (enemyShip.y - playerBullet.ypos)));
	float sumOfRadii = 25 + (enemyShip.h / 2);

	if (distance < sumOfRadii)
	{
		return true; // COLLISION!
	}
	else
	{
		return false; // NO COLLISION.
	}

	// return true if collision has occurred, otherwise, return false
}

void main()
{
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Game!");
	
	unsigned m = sfw::loadTextureMap("./res/106826.jpg");
	unsigned s = sfw::loadTextureMap("./res/rsH6n.png");
	unsigned b = sfw::loadTextureMap("./res/bullet.png");
	unsigned e = sfw::loadTextureMap("./res/paxship_05.gif");

	std::vector<bullet> bullets;
	ship player = {400, 50, 0, 0, 0, 0, &bullets};
	Enemy testEnemy;
	testEnemy.isAlive = true;
	testEnemy.x = 400;
	testEnemy.y = 500;
	testEnemy.w = 50;
	testEnemy.h = 50;
	testEnemy.xvel = 0;
	testEnemy.yvel = -350;

	testEnemy.textureId = e;
	
	sfw::setBackgroundColor(0x000099);

	bool isRunning = true;

	while (sfw::stepContext() && isRunning)
	{
	// Drawing everything
		sfw::drawTexture(m, 0, 600, 800, 600, 0, false, 0, 0x88888888);
		sfw::drawTexture(s, player.xpos, player.ypos, 50, 50);
		
		if (testEnemy.isAlive)
			testEnemy.draw();

		for (int i = 0; i < bullets.size(); ++i)
			if(bullets[i].alive)
				sfw::drawTexture(b, bullets[i].xpos, bullets[i].ypos, 50, 50);
	
	// Updating Everything
		player.update();
		testEnemy.update();
		for (int i = 0; i < bullets.size(); ++i)
			if(bullets[i].alive)
				bullets[i].update();

		for (int i = 0; i < bullets.size(); ++i)
		{
			if (bullets[i].alive)
			{
				// check for a collision between the enemy and the bullet
				if (testEnemy.isAlive && checkCollision(bullets[i], testEnemy))
				{
					testEnemy.isAlive = false;
				}
			}
		}
		

		if (sfw::getKey(KEY_ESCAPE)) break;
	}
	sfw::termContext();
}