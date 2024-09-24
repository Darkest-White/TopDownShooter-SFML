#include "Bullet.h"

Bullet::Bullet(Texture texture, Vector2f position, float angle) :
	GameObject(texture, position, angle, 0, 50, ObjType::Projectile)
{

}

Bullet::~Bullet()
{

}

void Bullet::Update(float dt)
{
	position.x += velocity * sin((angle * 3.14) / 180.0);
	position.y += velocity * -cos((angle * 3.14) / 180.0);

	lifeTime -= 15;

	if (lifeTime <= 0)
	{
		Message* msg = new Message;
		msg->type = MsgType::Death;
		msg->death.type = ObjType::Projectile;
		msg->sender = this;
		msg->death.who_to_die = this;
		msg->death.killer = this;
		GameManager::GetInstance()->SendMsg(msg);
	}
}