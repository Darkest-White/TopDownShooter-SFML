#include "Enemy.h"

Enemy::Enemy(Texture texture, Vector2f position, GameObject* target) :
	GameObject(texture, position, 0, 100, 50, ObjType::Enemy), target(target)
{
	sprite.setColor(Color::Red);
}

Enemy::~Enemy()
{

}

void Enemy::WatchTarget()
{
	angle = atan2f((target->GetPosition().x - sprite.getPosition().x), (sprite.getPosition().y - target->GetPosition().y)) * (180.0 / 3.14);
	sprite.setRotation(angle);
}

void Enemy::Move(float dt)
{
	position.x += (velocity * sin((angle * 3.14) / 180.0) * dt);
	position.y += (velocity * -cos((angle * 3.14) / 180.0) * dt);
}

void Enemy::Update(float dt)
{
	WatchTarget();
	Move(dt);
}

void Enemy::SendMSG(Message* msg)
{
	if (msg->deal_damage.to_who == this)
	{
		hp -= msg->deal_damage.damage;

		if (hp <= 0)
		{
			Message* m = new Message;
			m->type = MsgType::Death;
			m->death.type = ObjType::Enemy;
			m->sender = this;
			m->death.killer = msg->deal_damage.by_whom;
			m->death.who_to_die = this;
			GameManager::GetInstance()->SendMsg(m);
		}
	}
}