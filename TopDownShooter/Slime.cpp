#include "Slime.h"


Slime::Slime(Vector2f position, GameObject* target) :
	Enemy(ResourseManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	
}