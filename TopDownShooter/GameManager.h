#pragma once
#include"GameObject.h"
#include"Message.h"
#include"ResourseLoader.h"
#include<list>

class Player;

class GameManager
{
private:
	static GameManager* instance;

	list<GameObject*> players;
	list<GameObject*> enemies;
	list<GameObject*> projectiles;
	list<Message*> messages;

	int enemy_on_screen = 0;

	GameManager();
	~GameManager();

public:
	static GameManager* GetInstance();
	static void Destroy();

	void SpawnEnemy(GameObject* player, ResourseLoader loader, int win_width, int win_height);
	void SpawnBullet(Player* player, ResourseLoader loader);

	int GetCountEnemy();

	void CheckCollision();

	void Update(float dt);
	void SendMsg(Message* m);
	void DrawObjects(RenderWindow& window);
};