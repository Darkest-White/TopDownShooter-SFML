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
	window.create(sf::VideoMode(win_width, win_height), "The game");
	window.setVerticalSyncEnabled(true);

	ResourseLoader loader;

	loader.load("Actor.png");
	loader.load("Bullet.png");
	loader.load("NoTexture.png");

	Player player = Player(loader.getTextureByName("Actor.png"), { 400, 300 }, -50);
	int cooldown = 0;
	int enemyOnScreen = 0;
	int killsPoints = 0;

	Font font;
	font.loadFromFile("ARIAL.TTF");
	Text killsText;
	killsText.setFont(font);
	killsText.setFillColor(sf::Color::Black);
	killsText.setString(std::to_string(killsPoints));
	killsText.setCharacterSize(20);


	Clock clock;
	Time elapsed = clock.restart();
	const Time update_ms = sf::milliseconds(30.0f);
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
				enemyList.emplace_back(new Enemy(loader.getTextureByName("Actor.png"), { x, y }, 0));
				enemyOnScreen++;
			}

			if (!enemyList.empty()) for (auto enemy : enemyList)
			{
				enemy->runAI(player);
			}
			elapsed -= update_ms;
		}

		if (elapsed.asMilliseconds() > update_ms.asMilliseconds() / 2.0f)
		{
			cooldown += 15;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.goSide(3);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.goSide(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.goSide(7);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.goSide(5);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.goSide(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.goSide(2);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.goSide(4);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.goSide(6);

			window.clear(sf::Color(244, 164, 96, 255));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown >= 200)
			{
				bulletList.push_back(player.shootBullet(loader.getTextureByName("Bullet.png")));
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
			player.watchTarget(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			window.draw(player.sprite);
			killsText.setString(std::to_string(killsPoints));
			window.draw(killsText);
			window.display();
		}
	}

	return 0;
}