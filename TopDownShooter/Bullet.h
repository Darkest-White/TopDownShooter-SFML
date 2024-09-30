#pragma once
#include "Projectile.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Player.h"

class Bullet : public Projectile
{
public:
	Bullet(Vector2f position, float angle);
};

