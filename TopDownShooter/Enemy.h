#pragma once
#include "GameManager.h"
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	void MoveForward();
	void WatchTarget(GameObject target);
	float speed = 1.0;
	float angle;

public:
	Enemy(Texture texture, Vector2f position, float angle);
	~Enemy();
	void RunAI(GameObject);
	bool deleted;
};

