#include "Enemy.h"

Enemy::Enemy(Texture texture, Vector2f position, float angle) :
	GameObject(texture, position, ObjType::Enemy), angle(angle)
{
	sprite.setColor(Color(0, 100, 0));
	deleted = false;
}

Enemy::~Enemy()
{

}

void Enemy::RunAI(GameObject target)
{
	WatchTarget(target);
	MoveForward();
}

void Enemy::MoveForward()
{
	position.x += speed * sin((angle * 3.14) / 180.0);
	position.y += speed * -cos((angle * 3.14) / 180.0);
	UpdatePosition();
}

void Enemy::WatchTarget(GameObject target)
{
	angle = atan2f((target.GetPosition().x - sprite.getPosition().x), (sprite.getPosition().y - target.GetPosition().y)) * (180.0 / 3.14);
	sprite.setRotation(angle);
}