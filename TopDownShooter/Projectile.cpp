#include "Projectile.h"

Projectile::Projectile(Texture texture, Vector2f position, float angle, int damage) :
	GameObject(texture, position, angle, 0, damage, ObjType::Projectile)
{

}

Projectile::~Projectile()
{

}

void Projectile::Update(float dt)
{
	position.x += (velocity * sin((angle * 3.14) / 180.0)) * dt;
	position.y += (velocity * -cos((angle * 3.14) / 180.0)) * dt;

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

void Projectile::SendMSG(Message* msg)
{

}