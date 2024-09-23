#include "GameObject.h"


GameObject::GameObject(Texture texture, Vector2f position, ObjType type) :
	texture(texture), position(position), type(type)
{
	this->texture.setSmooth(true);
	CreateSprite();
}

GameObject::~GameObject()
{

}

void GameObject::CreateSprite()
{
	sprite.setTexture(texture, true);
	sprite.setPosition(position);
	sprite.setOrigin(sprite.getTextureRect().height / 2, sprite.getTextureRect().width / 2);
}

Vector2f GameObject::GetPosition()
{
	return position;
}

ObjType GameObject::GetType()
{
	return type;
}

void GameObject::checkCollision(GameObject target)
{

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