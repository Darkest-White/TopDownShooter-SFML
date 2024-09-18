#include "Entity.h"


Entity::Entity(Texture texture, Vector2f position) : texture(texture), position(position)
{
	this->texture.setSmooth(true);
	CreateSprite();
}


void Entity::CreateSprite()
{
	this->sprite.setTexture(texture, true);
	this->sprite.setPosition(position);
}


Vector2f Entity::GetPosition()
{
	return position;
}


bool Entity::checkCollision(Entity target)
{
	if(this->sprite.getGlobalBounds().intersects(target.sprite.getGlobalBounds())) return true;
	else return false;
}


void Entity::updatePosition()
{
	this->sprite.setPosition(position);
}


Entity::~Entity()
{
}