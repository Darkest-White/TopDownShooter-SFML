#pragma once
#include "Enemy.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ResourceManager.h"

class SlowSlime : public Enemy
{
private:

public:

	SlowSlime(Vector2f position, GameObject* target);
};