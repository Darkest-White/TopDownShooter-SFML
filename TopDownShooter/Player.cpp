#include "Player.h"

Player::Player(Texture texture, Vector2f position, float angle) :
	Entity(texture, position), angle(angle)
{
	sprite.setOrigin(sprite.getTextureRect().height / 2, sprite.getTextureRect().width / 2);
	sprite.setRotation(angle);
	deleted = false;
}


void Player::watchTarget(float x, float y)
{
	angle = atan2f((x - sprite.getPosition().x), (sprite.getPosition().y - y)) * (180.0 / 3.14);
	sprite.setRotation(Player::angle);
}


void Player::goSide(int side)
{
	if (side == 0)	 position.x += 5;
	if (side == 1) { position.x += 1.5; position.y += 1.5; }
	if (side == 2)   position.y += 5;
	if (side == 3) { position.x -= 1.5; position.y += 1.5; }
	if (side == 4)   position.x -= 5;
	if (side == 5) { position.x -= 1.5; position.y -= 1.5; }
	if (side == 6)   position.y -= 5;
	if (side == 7) { position.x += 1.5; position.y -= 1.5; }
	updatePosition();
}

Bullet* Player::shootBullet(Texture texture)
{
	Bullet* bullet = new Bullet(texture, position, angle, 25, 350);
	return bullet;
}

Player::~Player()
{
}