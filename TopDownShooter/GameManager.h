#pragma once
#include"GameObject.h"
#include"Message.h"
#include"ResourceManager.h"
#include<list>

class Player;

class GameManager
{
private:
	static GameManager* instance;

	ResourceManager* loader = ResourceManager::GetInstance();

	Player* player;
	list<GameObject*> enemies;
	list<GameObject*> projectiles;
	list<Message*> messages;

	int score = 0;
	bool game_over = false;

	GameManager();
	~GameManager();

public:
	static GameManager* GetInstance();
	static void Destroy();

	void SpawnPlayer(int x, int y);
	void SpawnEnemy(Player* player, int win_width, int win_height);
	void SpawnBullet(Player* player);

	int GetCountEnemy();
	Player* GetPlayer();
	int GetScore();
	bool GetGameStatus();
	bool GetMenuStatus();

	int enemy_on_screen = 0;
	bool menu = true;
	void ResetGame();

	void CheckCollision();

	void Update(float dt);
	void SendMsg(Message* m);
	void DrawObjects(RenderWindow& window);
};