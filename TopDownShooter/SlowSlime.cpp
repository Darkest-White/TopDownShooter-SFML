#include "SlowSlime.h"

SlowSlime::SlowSlime(Vector2f position, GameObject* target) :
	Enemy(ResourseManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	hp = 200;
	velocity = 0.5;
}