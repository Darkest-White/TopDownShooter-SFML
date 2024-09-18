#include "Bullet.h"
#include <functional>


Bullet::Bullet(Texture texture, Vector2f position, float angle, float speed, float lifetime) : 
	GameObject(texture, position, ObjType::Projectile), angle(angle), speed(speed), lifeTime(lifetime)
{
	this->deleted = false;
}


Bullet& Bullet::checkEveryFrame()
{
	position.x += speed * sin((angle * 3.14) / 180.0);
	position.y += speed * -cos((angle * 3.14) / 180.0);
	UpdatePosition();
	lifeTime -= 15;
	if (lifeTime <= 0) deleted = true;
	return *this;
}


Bullet::~Bullet()
{
}