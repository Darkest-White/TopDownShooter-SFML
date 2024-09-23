#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include "Bullet.h"
#include <math.h>

class Player : public GameObject
{
private:
	float angle;
	int hp = 100;
	float velocity = 1.5;

	bool game_over = false;

public:
	Player(Texture texture, Vector2f position, float angle);
	~Player();

	void GoSide(int side);
	void WatchTarget(float, float);

	float GetAngle();
	bool GetGameStatus();

	virtual void Update(float dt);
	virtual void SendMSG(Message* m);
};