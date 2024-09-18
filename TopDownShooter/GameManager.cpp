#include "SFML\Graphics.hpp"
#include "GameManager.h"
#include "Message.h"

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

void GameManager::Update(float dt)
{
	//spawnEnemy(dt);

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

		case MsgType::DamageToPlayer:
		{
			cout << "Player took " << m->damage_to_player.damage << " points of damage" << endl;
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