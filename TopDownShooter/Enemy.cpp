#include "Enemy.h"


Enemy::Enemy(Texture texture, Vector2f position, float angle = 0) :
	Entity(texture, position), angle(angle)
{
	sprite.setOrigin(sprite.getTextureRect().height / 2, sprite.getTextureRect().width / 2);
	sprite.setColor(Color(0, 100, 0));
	deleted = false;
}


void Enemy::runAI(Entity target)
{
	watchTarget(target);
	moveForward();
}


void Enemy::moveForward()
{
	position.x += speed * sin((angle * 3.14) / 180.0);
	position.y += speed * -cos((angle * 3.14) / 180.0);
	updatePosition();
}


void Enemy::watchTarget(Entity target)
{
	angle = atan2f((target.GetPosition().x - sprite.getPosition().x), (sprite.getPosition().y - target.GetPosition().y)) * (180.0 / 3.14);
	sprite.setRotation(angle);
}


Enemy::~Enemy()
{
}
