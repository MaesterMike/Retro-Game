#include <iostream>
#include "Header.h"
#include "sfwdraw.h"
#include "Bullet.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void main()
{
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Game!");
	
	unsigned m = sfw::loadTextureMap("./res/106826.jpg");
	unsigned s = sfw::loadTextureMap("./res/rsH6n.png");

	std::vector<bullet> bullets;
	ship player = {400, 50, 0, 0, 0, 0, &bullets};

	float acc = 0;
	char c = '\0';
	
	sfw::setBackgroundColor(0x000099);

	bool isRunning = true;

	while (sfw::stepContext() && isRunning)
	{
	// Drawing everything
		sfw::drawTexture(m, 0, 600, 800, 600, 0, false, 0, 0x88888888);
		sfw::drawTexture(s, player.xpos, player.ypos, 50, 50);

		for (int i = 0; i < bullets.size(); ++i)
			if(bullets[i].alive)
				sfw::drawTexture(s, bullets[i].xpos, bullets[i].ypos, 50, 50);
	
	// Updating Everything
		player.update();
		for (int i = 0; i < bullets.size(); ++i)
			if(bullets[i].alive)
				bullets[i].update();


		if (sfw::getKey(KEY_ESCAPE)) break;
		//player.xpos += player.xvel * sfw::getDeltaTime();

		//if (sfw::getKey(KEY_LEFT) && player.xvel == 0)
		//{
		//	player.xvel = -500;
		//	//player.xacc = 0;
		//}
		//else if (sfw::getKey(KEY_RIGHT) && player.xvel == 0)
		//{
		//	player.xvel = 500;
		//	//player.xacc = 0;
		//}
		//else
		//{
		//	player.xvel = 0;
		//}

		//if (sfw::getKey(KEY_SPACE))
		//{

		//}

		

		//if (player.xpos < 25)
		//{
		//	player.xpos = 25;
		//	player.xvel = 0;
		//}
		//else if (player.xpos > SCREEN_WIDTH - 25)
		//{
		//	player.xpos = SCREEN_WIDTH - 25;
		//	player.xvel = 0;
		//}


	}
	sfw::termContext();
}