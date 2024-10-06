#include "Bullet.h"

Bullet::Bullet(Vector2f position, float angle) :
	Projectile(ResourceManager::GetInstance()->GetTextureByName("Bullet.png"), position, angle, 50)
{

}