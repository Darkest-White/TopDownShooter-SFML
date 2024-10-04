#include "SlowSlime.h"

SlowSlime::SlowSlime(Vector2f position, GameObject* target) :
	Enemy(ResourceManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	hp = 200;
	velocity = 50;
}