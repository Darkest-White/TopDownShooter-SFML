#pragma once
#include "GameObject.h"
#include "GameManager.h"

class Projectile : public GameObject
{
protected:
	float velocity = 25;
	float lifeTime = 350;

public:
	Projectile(Texture texture, Vector2f position, float angle, int damage);
	~Projectile();

	virtual void Update(float dt);
	virtual void SendMSG(Message* msg);
};