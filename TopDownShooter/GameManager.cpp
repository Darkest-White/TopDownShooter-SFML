#include "SFML\Graphics.hpp"
#include "GameManager.h"

#include"Slime.h"
#include"FastSlime.h"
#include"SlowSlime.h"
#include"Player.h"
#include"Bullet.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() : enemies(), projectiles(), messages()
{

}

GameManager::~GameManager()
{
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

void GameManager::SpawnPlayer(int x, int y)
{
	Vector2f position;
	position.x = x;
	position.y = y;
	player = new Player(loader->GetTextureByName("Actor.png"), position);
}

void GameManager::SpawnEnemy(Player* player, int win_width, int win_height)
{
	float x = rand() % win_width, y = rand() % win_height;

	while (!((x >= player->GetPosition().x + 120) || (x <= player->GetPosition().y - 120)) &&
		!((y >= player->GetPosition().y + 120) || (y <= player->GetPosition().y - 120)))
	{
		x = rand() % win_width;
		y = rand() % win_height;
	}

	int rand_x = rand() % 101;

	if (rand_x < 33)
	{
		Message* msg = new Message;
		msg->type = MsgType::Create;
		msg->create.type = ObjType::Enemy;
		Slime* e = new Slime({ x, y }, player);
		msg->create.new_object = e;
		SendMsg(msg);
		enemy_on_screen++;
	}

	if (rand_x > 33 && rand_x < 66)
	{
		Message* msg = new Message;
		msg->type = MsgType::Create;
		msg->create.type = ObjType::Enemy;
		FastSlime* e = new FastSlime({ x, y }, player);
		msg->create.new_object = e;
		SendMsg(msg);
		enemy_on_screen++;
	}

	if (rand_x > 66)
	{
		Message* msg = new Message;
		msg->type = MsgType::Create;
		msg->create.type = ObjType::Enemy;
		SlowSlime* e = new SlowSlime({ x, y }, player);
		msg->create.new_object = e;
		SendMsg(msg);
		enemy_on_screen++;
	}
}

void GameManager::SpawnBullet(Player* player)
{
	Message* msg = new Message;
	msg->type = MsgType::Create;
	msg->create.type = ObjType::Projectile;
	Bullet* b = new Bullet(player->GetPosition(), player->GetAngle());
	msg->create.new_object = b;
	SendMsg(msg);
}

int GameManager::GetCountEnemy()
{
	return enemy_on_screen;
}

Player* GameManager::GetPlayer()
{
	return player;
}

int GameManager::GetScore()
{
	return score;
}

bool GameManager::GetGameStatus()
{
	return game_over;
}

bool GameManager::GetMenuStatus()
{
	return menu;
}

void GameManager::ResetGame()
{
	game_over = false;
	menu = true;
	
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

	player->Renewal();
	score = 0;
	enemy_on_screen = 0;
}

void GameManager::CheckCollision()
{
	if (!projectiles.empty())
	{
		for (auto bullet : projectiles)
		{
			for (auto enemy : enemies)
			{
				if (enemy->checkCollision(bullet))
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

	if (!enemies.empty())
	{
		for (auto enemy : enemies)
		{
			if (enemy->checkCollision(player))
			{
				Message* msg = new Message;
				msg->type = MsgType::DealDamage;
				msg->deal_damage.by_whom = enemy;
				msg->deal_damage.damage = enemy->GetDamage();
				msg->deal_damage.to_who = player;
				msg->sender = enemy;
				SendMsg(msg);

				msg = new Message;
				msg->type = MsgType::Death;
				msg->death.type = ObjType::Enemy;
				msg->death.killer = enemy;
				msg->death.who_to_die = enemy;
				msg->sender = enemy;
				SendMsg(msg);
			}
		}
	}
}

void GameManager::Update(float dt)
{
	player->Update(dt);
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
			if (msg->death.type == ObjType::Player)
			{
				game_over = true;
			}
			if (msg->death.type == ObjType::Enemy)
			{
				auto res = find(enemies.begin(), enemies.end(), msg->death.who_to_die);
				if (res != enemies.end())
				{
					delete* res;
					enemies.erase(res);
					enemy_on_screen--;
				}
				score += 10;
			}
			if (msg->death.type == ObjType::Projectile)
			{
				auto res = find(projectiles.begin(), projectiles.end(), msg->death.who_to_die);
				if (res != projectiles.end())
				{
					delete* res;
					projectiles.erase(res);
				}
			}
		} break;

		case MsgType::Create:
		{
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
			player->SendMSG(msg);
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
	player->Draw(window);
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