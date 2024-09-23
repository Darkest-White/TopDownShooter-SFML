#pragma once
#include "GameManager.h"
#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
private:
	void MoveForward();
	void WatchTarget();
	float velocity = 100;
	float angle;
	int damage = 50;

	GameObject* target;
	Vector2f direction;

public:
	Enemy(Texture texture, Vector2f position, float angle, GameObject* player);
	~Enemy();

	virtual void Update(float dt);
	bool deleted;
};
