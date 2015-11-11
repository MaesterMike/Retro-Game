#include <iostream>
#include "Header.h"
#include "sfwdraw.h"

void main()
{
	sfw::initContext(800, 600, "Retro Game!");

	unsigned m = sfw::loadTextureMap("./res/106826.jpg");
	unsigned s = sfw::loadTextureMap("./res/rsH6n.png");

	float acc = 0;
	char c = '\0';

	sfw::setBackgroundColor(0x000099);

	while (sfw::stepContext())
	{
		sfw::drawTexture(m, 0, 600, 800, 600, 0, false, 0, 0x88888888);
		sfw::drawTexture(s, 50, 50, 50, 50);

		if (sfw::getKey(KEY_ESCAPE)) break;
	}

	sfw::termContext();
}