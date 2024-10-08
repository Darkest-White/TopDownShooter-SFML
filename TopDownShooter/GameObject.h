#include "SFML\Graphics.hpp"
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
	int hp;
	int damage;
	float angle;
	ObjType type;

	Texture texture;
	Sprite sprite;
	void CreateSprite();

public:
	GameObject(Texture texture, Vector2f position, float angle, int hp, int damage, ObjType type);
	virtual ~GameObject();

	virtual bool checkCollision(GameObject* target);

	virtual Vector2f GetPosition();
	virtual int GetHP();
	virtual int GetDamage();
	virtual float GetAngle();
	virtual ObjType GetType();

	virtual void Update(float dt) = 0;
	virtual void SendMSG(Message* m) = 0;
	void Draw(RenderWindow& window);
};