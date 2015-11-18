#pragma once
#include "GameObject.h"

class GameState;

class Player : public GameObject
{
public:
	float speed;
	float fireDelay;
	float rateOfFire;

	Player() : speed(100), rateOfFire(0.1f), fireDelay(0.f)
	{
		width = 200; height = 200;
		animationName       = "NOTVERYBOOM";
		textureName         = "Explosion";
	}

	virtual void onCollision(GameObject &go, float distance)
	{
		animTimer = 0;
		animationName = "NOTVERYBOOM";
	}

	virtual void update();
};