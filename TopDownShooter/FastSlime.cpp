#include "FastSlime.h"

FastSlime::FastSlime(Vector2f position, GameObject* target) :
	Enemy(ResourceManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	hp = 50;
	velocity = 200;
}