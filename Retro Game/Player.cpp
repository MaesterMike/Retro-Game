#include "GameState.h"
#include "Player.h"

void Player::update()
{
	fireDelay -= sfw::getDeltaTime();
	//example of switching between animations
	if (sfw::getKey(' ') && fireDelay < 0)
	{
		fireDelay = rateOfFire;
		gs()->makeBullet(x, y, 0, 300, 4.f);
	}

	if (animTimer > getAnimationDuration(textureName, animationName))
	{
		animTimer = 0;
		animationName = "BOOM";
	}
	
	// speed scaled by delta time
	//
	float sdt = sfw::getDeltaTime() * speed;
	if (sfw::getKey('W')) y -= sdt;	// up
	if (sfw::getKey('S')) y += sdt; // down
	if (sfw::getKey('A')) x -= sdt; // left
	if (sfw::getKey('D')) x += sdt; // right
}