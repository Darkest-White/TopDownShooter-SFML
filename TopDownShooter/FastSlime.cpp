#include "FastSlime.h"

FastSlime::FastSlime(Vector2f position, GameObject* target) :
	Enemy(ResourceManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	hp = 50;
	velocity = 200;
}

void FastSlime::Update(float dt)
{
	WatchTarget();
	if (!is_paused)
	{
		Move(dt);
		timer += dt;
	}

	if (timer >= move_time)
	{
		is_paused = true;
		timer = 0;
	}
	else
	{
		timer += dt;
		if (timer >= pause_time)
		{
			is_paused = false;
			timer = 0;
		}
	}
}