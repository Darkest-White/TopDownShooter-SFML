#include "Bullet.h"
#include <functional>

Bullet::Bullet(Texture texture, Vector2f position, float angle) :
	GameObject(texture, position, ObjType::Projectile),
	angle(angle)
{
	this->deleted = false;
}

Bullet::~Bullet()
{

}

//Bullet& Bullet::checkEveryFrame()
//{
//	
//}

void Bullet::Update(float dt)
{
	position.x += velocity * sin((angle * 3.14) / 180.0);
	position.y += velocity * -cos((angle * 3.14) / 180.0);
	lifeTime -= 15;

	if (lifeTime <= 0)
	{
		Message* m = new Message;
		m->type = MsgType::Death;
		m->death.who_to_die = this;
		m->death.killer = this;
		GameManager::GetInstance()->SendMsg(m);
	}
}