#include <string>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "ResourseLoader.h"
#include <iostream>
using namespace std;
using namespace sf;

#pragma once
class Entity
{
private:
	Texture texture;
	void CreateSprite();

protected:
	void updatePosition();
	Vector2f position;

public:
	Entity(Texture texture, Vector2f position);

	bool checkCollision(Entity);
	Vector2f GetPosition();
	Sprite sprite;

	virtual ~Entity();
};

