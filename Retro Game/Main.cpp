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
	unsigned x = sfw::loadTextureMap("./res/spritesheet1.png");

	std::vector<bullet> bullets;
	ship player = {400, 50, 0, 0, 0, 0, &bullets};
	
	
	std::vector<Enemy> enemies;
	for (int j = 0; j < 30; ++j)
	{
			enemies.push_back(Enemy());
			enemies[j].isAlive = true;
			enemies[j].x = rand() % 600 + 100;
			enemies[j].y = 625;
			enemies[j].w = 50;
			enemies[j].h = 50;
			enemies[j].xvel = 0;
			enemies[j].yvel = -250;
			enemies[j].textureId = e;
	}
	

	Enemy testEnemy;
	testEnemy.isAlive = true;
	testEnemy.x = 400;
	testEnemy.y = 625;
	testEnemy.w = 50;
	testEnemy.h = 50;
	testEnemy.xvel = 0;
	testEnemy.yvel = -250;

	testEnemy.textureId = e;
	
	sfw::setBackgroundColor(0x000099);

	bool isRunning = true;

	while (sfw::stepContext() && isRunning)
	{
	// Drawing everything
		sfw::drawTexture(m, 0, 600, 800, 600, 0, false, 0, 0x88888888);
		sfw::drawTexture(s, player.xpos, player.ypos, 50, 50);
		


//////////////////////////////////////////////////////////////
		for (int i = 0; i < enemies.size(); ++i)
			if(enemies[i].isAlive)
				enemies[i].draw();

		if (testEnemy.isAlive)
			testEnemy.draw();
//////////////////////////////////////////////////////////////


		for (int i = 0; i < bullets.size(); ++i)
			if(bullets[i].alive)
				sfw::drawTexture(b, bullets[i].xpos, bullets[i].ypos, 50, 50);
	
	// Updating Everything
		player.update();
		testEnemy.update();
		for (int i = 0; i < enemies.size(); ++i)
			if (enemies[i].isAlive)
				enemies[i].update();

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

				for (int j = 0; j < enemies.size(); ++j)
					if (enemies[j].isAlive && checkCollision(bullets[i], enemies[j]))
					{
						enemies[j].isAlive = false;
						bullets[i].alive = false;
					}
			}
		}
		
		if (sfw::getKey(KEY_ESCAPE)) break;

		if (!testEnemy.isAlive)
		{
			testEnemy.isAlive = true;
			testEnemy.x = rand()%600+100;
			testEnemy.y = 625;
			testEnemy.w = 50;
			testEnemy.h = 50;
			testEnemy.xvel = 0;
			testEnemy.yvel = -250;
		}
		for (int j = 0; j < enemies.size(); ++j)
		if (!enemies[j].isAlive)
		{
			enemies[j].isAlive = true;
			enemies[j].x = rand() % 600 + 100;
			enemies[j].y = 625;
			enemies[j].w = 50;
			enemies[j].h = 50;
			enemies[j].xvel = 0;
			enemies[j].yvel = -250;
		}
	}
	sfw::termContext();
}