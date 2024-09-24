#pragma once
#include"GameObject.h"
#include"Message.h"
#include"ResourseManager.h"
#include<list>

class Player;

class GameManager
{
private:
	static GameManager* instance;

	Player* player;

	list<GameObject*> enemies;
	list<GameObject*> projectiles;
	list<Message*> messages;

	int enemy_on_screen = 0;
	bool game_over = false;

	GameManager();
	~GameManager();

public:
	static GameManager* GetInstance();
	static void Destroy();

	void SpawnPlayer(int x, int y, ResourseManager* loader);
	void SpawnEnemy(Player* player, ResourseManager* loader, int win_width, int win_height);
	void SpawnBullet(Player* player, ResourseManager* loader);

	int GetCountEnemy();
	Player* GetPlayer();
	bool GetGameStatus();

	void CheckCollision();

	void Update(float dt);
	void SendMsg(Message* m);
	void DrawObjects(RenderWindow& window);
};