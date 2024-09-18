#pragma once
#include "Entity.h"
class Enemy : public Entity
{
private:
	void moveForward();
	void watchTarget(Entity);
	float speed = 1.0;
	float angle;
public:
	Enemy(Texture texture, Vector2f position, float angle);
	void runAI(Entity);
	bool deleted;
	~Enemy();

};

