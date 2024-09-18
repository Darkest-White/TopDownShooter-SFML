#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include <algorithm>
#include <list>
#include "Enemy.h"
#include "ResourseLoader.h"

int main()
{
	int win_width = 1600;
	int win_height = 900;
	RenderWindow window;
	window.create(VideoMode(win_width, win_height), "TopDownShooter");
	window.setVerticalSyncEnabled(true);

	ResourseLoader loader;

	loader.Load("Actor.png");
	loader.Load("Bullet.png");
	loader.Load("NoTexture.png");

	Player player = Player(loader.GetTextureByName("Actor.png"), { 400, 300 }, -50);
	int cooldown = 0;
	int enemyOnScreen = 0;
	int killsPoints = 0;

	Font font;
	font.loadFromFile("ARIAL.TTF");
	Text killsText;
	killsText.setFont(font);
	killsText.setFillColor(Color::Black);
	killsText.setString(to_string(killsPoints));
	killsText.setCharacterSize(20);


	Clock clock;
	Time elapsed = clock.restart();
	const Time update_ms = milliseconds(30.0f);
	list<Bullet*> bulletList;
	list<Enemy*> enemyList;



	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (player.deleted)
				window.close();
		}

		elapsed += clock.restart();
		if (elapsed.asMilliseconds() >= update_ms.asMilliseconds())
		{
			while (enemyOnScreen < 10)
			{
				float x = rand() % win_width, y = rand() % win_height;
				while (!((x >= player.GetPosition().x + 50) || (x <= player.GetPosition().y - 50)) ||
					!((y >= player.GetPosition().y + 50) || (y <= player.GetPosition().y - 50)))
				{
					x = rand() % 800;
					y = rand() % 600;
				}
				enemyList.emplace_back(new Enemy(loader.GetTextureByName("Actor.png"), { x, y }, 0));
				enemyOnScreen++;
			}

			if (!enemyList.empty()) for (auto enemy : enemyList)
			{
				enemy->RunAI(player);
			}
			elapsed -= update_ms;
		}

		if (elapsed.asMilliseconds() > update_ms.asMilliseconds() / 2.0f)
		{
			cooldown += 15;
			if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) player.GoSide(3);
			if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S)) player.GoSide(1);
			if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W)) player.GoSide(7);
			if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W)) player.GoSide(5);
			if (Keyboard::isKeyPressed(Keyboard::D)) player.GoSide(0);
			if (Keyboard::isKeyPressed(Keyboard::S)) player.GoSide(2);
			if (Keyboard::isKeyPressed(Keyboard::A)) player.GoSide(4);
			if (Keyboard::isKeyPressed(Keyboard::W)) player.GoSide(6);

			window.clear(Color(244, 164, 96, 255));

			if (Mouse::isButtonPressed(Mouse::Left) && cooldown >= 200)
			{
				bulletList.push_back(player.ShootBullet(loader.GetTextureByName("Bullet.png")));
				cooldown = 0;
			}
			if (!bulletList.empty()) for (auto bullet : bulletList)
			{
				window.draw(bullet->checkEveryFrame().sprite);
				for (auto enemy : enemyList)
				{
					if (enemy->checkCollision(*bullet))
					{
						enemy->deleted = true;
						bullet->deleted = true;
						enemyOnScreen--;
						killsPoints++;
					}
				}
			}
			bulletList.remove_if([](Bullet* n) { return n->deleted == true; });
			enemyList.remove_if([](Enemy* n) { return n->deleted == true; });
			if (!enemyList.empty()) for (auto enemy : enemyList)
			{
				window.draw(enemy->sprite);
				if (enemy->checkCollision(player)) player.deleted = true;
			}
			player.WatchTarget(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
			window.draw(player.sprite);
			killsText.setString(to_string(killsPoints));
			window.draw(killsText);
			window.display();
		}
	}

	return 0;
}