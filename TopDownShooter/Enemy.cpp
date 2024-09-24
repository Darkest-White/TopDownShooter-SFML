#include "Enemy.h"

Enemy::Enemy(Texture texture, Vector2f position, GameObject* target) :
	GameObject(texture, position, 0, ObjType::Enemy), target(target)
{
	sprite.setColor(Color(0, 100, 0));
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
	Vector2f target_position = target->GetPosition();
	Vector2f vector_to_target = target_position - position;
	float distance_to_target = GetLenght(vector_to_target);

	//static float cooldown = 0;
	//if (cooldown > 0) cooldown -= dt;
	if (velocity * dt >= distance_to_target /*&& cooldown <= 0*/)
	{
		//cooldown = 0.05;

		Message* m = new Message;
		m->type = MsgType::DealDamage;
		m->sender = this;
		m->deal_damage.by_whom = this;
		m->deal_damage.damage = damage;
		m->deal_damage.to_who = target;
		GameManager::GetInstance()->SendMsg(m);
	}

	direction = Normalize(vector_to_target);

	position.x += direction.x * velocity * dt;
	position.y += direction.y * velocity * dt;

	//position.x += velocity * sin((angle * 3.14) / 180.0);
	//position.y += velocity * -cos((angle * 3.14) / 180.0);
}

void Enemy::Update(float dt)
{
	WatchTarget();
	Move(dt);
}