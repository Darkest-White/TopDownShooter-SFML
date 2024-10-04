#pragma once
#include "GameObject.h"
#include "GameManager.h"

class Player : public GameObject
{
private:
	int hp = 100;
	float velocity = 150;

public:
	Player(Texture texture, Vector2f position);
	~Player();

	void WatchTarget(float mouse_x, float mouse_y);
	void GoSide(int side, float dt);

	void Renewal();

	virtual void Update(float dt);
	virtual void SendMSG(Message* m);
};