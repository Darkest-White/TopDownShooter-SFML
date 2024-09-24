#include "SFML\Graphics.hpp"
#include "GameManager.h"

#include"Enemy.h"
#include"Player.h"
#include"Bullet.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() : players(), enemies(), projectiles(), messages()
{

}

GameManager::~GameManager()
{
	for (auto x : players)
	{
		delete x;
	}
	players.clear();

	for (auto x : enemies)
	{
		delete x;
	}
	enemies.clear();

	for (auto x : projectiles)
	{
		delete x;
	}
	projectiles.clear();

	for (auto x : messages)
	{
		delete x;
	}
	messages.clear();
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
	msg->create.type = ObjType::Enemy;
	Enemy* e = new Enemy(loader.GetTextureByName("Actor.png"), { x, y }, player);
	msg->create.new_object = e;
	SendMsg(msg);

	enemy_on_screen++;
}

void GameManager::SpawnBullet(Player* player, ResourseLoader loader)
{
	Message* msg = new Message;
	msg->type = MsgType::Create;
	msg->create.type = ObjType::Projectile;
	Bullet* b = new Bullet(loader.GetTextureByName("Bullet.png"), player->GetPosition(), player->GetAngle());
	msg->create.new_object = b;
	SendMsg(msg);
}

int GameManager::GetCountEnemy()
{
	return enemy_on_screen;
}

void GameManager::CheckCollision()
{
	if (!projectiles.empty())
	{
		for (auto bullet : projectiles)
		{
			for (auto enemy : enemies)
			{
				if (enemy->checkCollision(*bullet))
				{
					Message* msg = new Message;
					msg->type = MsgType::DealDamage;
					msg->deal_damage.by_whom = bullet;
					msg->deal_damage.damage = bullet->GetDamage();
					msg->deal_damage.to_who = enemy;
					msg->sender = bullet;
					SendMsg(msg);

					msg = new Message;
					msg->type = MsgType::Death;
					msg->death.type = ObjType::Projectile;
					msg->death.killer = bullet;
					msg->death.who_to_die = bullet;
					msg->sender = bullet;
					SendMsg(msg);
				}
			}
		}
	}
}

void GameManager::Update(float dt)
{
	for (auto obj : players)
	{
		obj->Update(dt);
	}
	for (auto obj : enemies)
	{
		obj->Update(dt);
	}
	for (auto obj : projectiles)
	{
		obj->Update(dt);
	}

	CheckCollision();

	Message* msg;
	while (!messages.empty())
	{
		msg = messages.front();
		messages.pop_front();
		switch (msg->type)
		{
		case MsgType::Death:
		{
			if (msg->create.type == ObjType::Player)
			{
				auto res = find(players.begin(), players.end(), msg->death.who_to_die);
				delete* res;
				players.erase(res);
			}
			if (msg->create.type == ObjType::Enemy)
			{
				auto res = find(enemies.begin(), enemies.end(), msg->death.who_to_die);
				delete* res;
				enemies.erase(res);
				enemy_on_screen--;
			}
			if (msg->create.type == ObjType::Projectile)
			{
				auto res = find(projectiles.begin(), projectiles.end(), msg->death.who_to_die);
				delete* res;
				projectiles.erase(res);
			}
		} break;

		case MsgType::Create:
		{
			if (msg->create.type == ObjType::Player)
			{
				players.push_back(msg->create.new_object);
			}
			if (msg->create.type == ObjType::Enemy)
			{
				enemies.push_back(msg->create.new_object);
			}
			if (msg->create.type == ObjType::Projectile)
			{
				projectiles.push_back(msg->create.new_object);
			}
		} break;
		}

		if (msg->type == MsgType::DealDamage)
		{
			for (auto obj : players)
			{
				obj->SendMSG(msg);
			}
			for (auto obj : enemies)
			{
				obj->SendMSG(msg);
			}
		}
		delete msg;
	}
}

void GameManager::SendMsg(Message* m)
{
	messages.push_back(m);
}

void GameManager::DrawObjects(RenderWindow& window)
{
	for (auto obj : players)
	{
		obj->Draw(window);
	}
	for (auto obj : enemies)
	{
		obj->Draw(window);
	}
	for (auto obj : projectiles)
	{
		obj->Draw(window);
	}
}

void GameManager::Destroy()
{
	if (instance) delete instance;
	instance = nullptr;
}