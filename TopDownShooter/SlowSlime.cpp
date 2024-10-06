#include "SlowSlime.h"

SlowSlime::SlowSlime(Vector2f position, GameObject* target) :
	Enemy(ResourceManager::GetInstance()->GetTextureByName("Actor.png"), position, target)
{
	hp = 200;
	velocity = 50;
}

void SlowSlime::SendMSG(Message* msg)
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

			m = new Message;
			m->type = MsgType::Create;
			m->create.type = ObjType::Enemy;
			Slime* e = new Slime({ position.x - 10, position.y }, target);
			m->create.new_object = e;
			GameManager::GetInstance()->SendMsg(m);
			GameManager::GetInstance()->enemy_on_screen++;

			m = new Message;
			m->type = MsgType::Create;
			m->create.type = ObjType::Enemy;
			e = new Slime({ position.x + 10, position.y }, target);
			m->create.new_object = e;
			GameManager::GetInstance()->SendMsg(m);
			GameManager::GetInstance()->enemy_on_screen++;
		}
	}
}