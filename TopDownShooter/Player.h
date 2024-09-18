#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <math.h>
class Player : public Entity
{
private:
	float angle;

public:
	Player(Texture texture, Vector2f position, float angle = 0);
	~Player();

	void goSide(int);
	void watchTarget(float, float);
	Bullet* shootBullet(Texture);
	bool deleted;
};

