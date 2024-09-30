#include "Bullet.h"

Bullet::Bullet(Vector2f position, float angle) :
	Projectile(ResourseManager::GetInstance()->GetTextureByName("Bullet.png"), position, angle)
{

}