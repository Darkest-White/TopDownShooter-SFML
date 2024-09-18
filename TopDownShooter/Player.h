#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include "Bullet.h"
#include <math.h>

class Player : public GameObject
{
private:
	float angle;

public:
	Player(Texture texture, Vector2f position, float angle);
	~Player();

	void GoSide(int);
	void WatchTarget(float, float);
	Bullet* ShootBullet(Texture);
	bool deleted;
};