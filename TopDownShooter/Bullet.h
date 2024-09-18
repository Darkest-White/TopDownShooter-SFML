#pragma once
#include "Entity.h"
class Bullet : public Entity
{
private:
	float speed;
	float angle;
	float lifeTime;

public:
	Bullet(Texture texture, Vector2f position, float angle = 0, float speed = 0, float lifetime = 0);
	Bullet& checkEveryFrame();
	~Bullet();
	bool deleted;
};

