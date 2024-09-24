#include "SFML\Graphics.hpp"
#include "ResourseLoader.h"
#include "VectorMath.h"
#include <iostream>
using namespace std;
using namespace sf;

struct Message;
enum class ObjType;

#pragma once
class GameObject
{
protected:
	Vector2f position;
	float angle;
	ObjType type;

	Texture texture;
	Sprite sprite;
	void CreateSprite();

public:
	GameObject(Texture texture, Vector2f position, float angle, ObjType type);
	virtual ~GameObject();

	virtual void checkCollision(GameObject target);

	virtual Vector2f GetPosition();
	virtual float GetAngle();
	virtual ObjType GetType();

	virtual void Update(float dt);
	virtual void SendMSG(Message* m);
	void Draw(RenderWindow& window);
};