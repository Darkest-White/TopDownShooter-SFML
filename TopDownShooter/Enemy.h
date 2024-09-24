#pragma once
#include "GameManager.h"
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	int damage = 50;
	float velocity = 100;

	GameObject* target;
	Vector2f direction;

	void WatchTarget();
	void Move(float dt);

public:
	Enemy(Texture texture, Vector2f position, GameObject* player);
	~Enemy();

	virtual void Update(float dt);
};
