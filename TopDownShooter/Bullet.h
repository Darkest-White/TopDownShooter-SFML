#pragma once
#include "GameObject.h"
#include "GameManager.h"

class Bullet : public GameObject
{
private:
	float velocity = 25;
	float angle;
	float lifeTime = 350;

public:
	Bullet(Texture texture, Vector2f position, float angle = 0);
	~Bullet();

	Bullet& checkEveryFrame();
	bool deleted;

	virtual void Update(float dt);
};

