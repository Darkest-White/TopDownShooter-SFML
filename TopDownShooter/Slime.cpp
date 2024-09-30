#include "Slime.h"

Slime::Slime(Vector2f position, GameObject* target) :
	Enemy(ResourceManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{

}