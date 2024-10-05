#pragma once
#include "GameManager.h"
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	float velocity = 100;

	GameObject* target;

	void WatchTarget();
	virtual void Move(float dt);

public:
	Enemy(Texture texture, Vector2f position, GameObject* player);
	~Enemy();

	virtual void Update(float dt);
	virtual void SendMSG(Message* msg);
};