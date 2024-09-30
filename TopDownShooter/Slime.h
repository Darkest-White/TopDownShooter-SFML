#pragma once
#include "Enemy.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ResourseManager.h"

class Slime : public Enemy
{
private:

public:

	Slime(Vector2f position, GameObject* target);
};