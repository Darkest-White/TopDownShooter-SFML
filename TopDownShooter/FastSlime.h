#pragma once
#include "Enemy.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ResourceManager.h"

class FastSlime : public Enemy
{
private:

public:

	FastSlime(Vector2f position, GameObject* target);
};