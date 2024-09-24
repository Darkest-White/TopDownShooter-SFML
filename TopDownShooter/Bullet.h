#pragma once
#include "GameObject.h"
#include "GameManager.h"

class Bullet : public GameObject
{
protected:
	float velocity = 25;
	float lifeTime = 350;

public:
	Bullet(Texture texture, Vector2f position, float angle);
	~Bullet();

	virtual void Update(float dt);
};

