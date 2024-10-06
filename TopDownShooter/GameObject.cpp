#include "GameObject.h"

GameObject::GameObject(Texture texture, Vector2f position, float angle, int hp, int damage, ObjType type) :
	texture(texture), position(position), angle(angle), hp(hp), damage(damage), type(type)
{
	this->texture.setSmooth(true);
	CreateSprite();
	sprite.setRotation(angle);
}

GameObject::~GameObject()
{

}

void GameObject::CreateSprite()
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setOrigin(sprite.getTextureRect().height / 2, sprite.getTextureRect().width / 2);
}

Vector2f GameObject::GetPosition()
{
	return position;
}

int GameObject::GetDamage()
{
	return damage;
}

int GameObject::GetHP()
{
	return hp;
}

float GameObject::GetAngle()
{
	return angle;
}

ObjType GameObject::GetType()
{
	return type;
}

bool GameObject::checkCollision(GameObject* target)
{
	if (this->sprite.getGlobalBounds().intersects(target->sprite.getGlobalBounds())) return true;
	else return false;
}

void GameObject::Update(float dt)
{

}

void GameObject::SendMSG(Message* m)
{

}

void GameObject::Draw(RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}