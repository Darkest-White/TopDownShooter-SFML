#include "SFML\Graphics.hpp"
#include "GameManager.h"

#include"Enemy.h"
#include"Player.h"
#include"Bullet.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() : objs(), msgs()
{

}

GameManager::~GameManager()
{
	for (auto x : objs)
	{
		delete x;
	}
	objs.clear();

	for (auto x : msgs)
	{
		delete x;
	}
	msgs.clear();
}

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr) instance = new GameManager();
	return instance;
}

void GameManager::SpawnEnemy(GameObject* player, ResourseLoader loader, int win_width, int win_height)
{
	float x = rand() % win_width, y = rand() % win_height;
	while (!((x >= player->GetPosition().x + 50) || (x <= player->GetPosition().y - 50)) ||
		!((y >= player->GetPosition().y + 50) || (y <= player->GetPosition().y - 50)))
	{
		x = rand() % 800;
		y = rand() % 600;
	}

	Message* msg = new Message;
	msg->type = MsgType::Create;
	Enemy* b = new Enemy(loader.GetTextureByName("Actor.png"), { x, y }, player);
	msg->create.new_object = b;
	SendMsg(msg);
}

void GameManager::SpawnBullet(Player* player, ResourseLoader loader)
{
	Message* msg = new Message;
	msg->type = MsgType::Create;
	Bullet* b = new Bullet(loader.GetTextureByName("Bullet.png"), player->GetPosition(), player->GetAngle());
	msg->create.new_object = b;
	SendMsg(msg);
}

void GameManager::Update(float dt)
{
	for (auto obj : objs)
	{
		obj->Update(dt);
	}

	Message* m;
	while (!msgs.empty())
	{
		m = msgs.front();
		msgs.pop_front();
		switch (m->type)
		{
		case MsgType::Death:
		{
			auto res = find(objs.begin(), objs.end(), m->death.who_to_die);
			delete* res;
			objs.erase(res);
		} break;

		case MsgType::Create:
		{
			objs.push_back(m->create.new_object);
		} break;
		}

		if (m->type == MsgType::Move ||
			m->type == MsgType::DealDamage ||
			m->type == MsgType::Death)
		{
			for (auto obj : objs)
			{
				obj->SendMSG(m);
			}
		}
		delete m;
	}
}

void GameManager::SendMsg(Message* m)
{
	msgs.push_back(m);
}

void GameManager::DrawObjects(RenderWindow& window)
{
	for (auto obj : objs)
	{
		obj->Draw(window);
	}
}

void GameManager::Destroy()
{
	if (instance) delete instance;
	instance = nullptr;
}