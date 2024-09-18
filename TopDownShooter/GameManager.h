#pragma once
#include"GameObject.h"
#include<list>

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

	//void spawnEnemy(float dt);

	void Update(float dt);
	void SendMsg(Message* m);
	void DrawObjects(RenderWindow& window);
};