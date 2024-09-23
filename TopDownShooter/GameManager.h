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

	list<GameObject*> objs;
	list<Message*> msgs;

	GameManager();
	~GameManager();

public:
	static GameManager* GetInstance();
	static void Destroy();

	void SpawnEnemy(GameObject* player, ResourseLoader loader, int win_width, int win_height);
	void SpawnBullet(Player* player, ResourseLoader loader);

	void Update(float dt);
	void SendMsg(Message* m);
	void DrawObjects(RenderWindow& window);
};