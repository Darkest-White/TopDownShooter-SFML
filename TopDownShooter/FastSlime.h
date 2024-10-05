#pragma once
#include "Enemy.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ResourceManager.h"

class FastSlime : public Enemy
{
private:
	float timer = 0;
	float move_time = 2;
	float pause_time = 2;
	bool is_paused = false;

public:

	FastSlime(Vector2f position, GameObject* target);

	virtual void Update(float dt);
};