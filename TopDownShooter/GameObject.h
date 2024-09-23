#include <string>
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
private:
	Texture texture;
	void CreateSprite();

protected:
	Vector2f position;
	ObjType type;

public:
	GameObject(Texture texture, Vector2f position, ObjType type);
	virtual ~GameObject();

	Sprite sprite;
	virtual void checkCollision(GameObject target);

	virtual Vector2f GetPosition();
	virtual ObjType GetType();

	virtual void Update(float dt);
	virtual void SendMSG(Message* m);
	void Draw(RenderWindow& window);
};