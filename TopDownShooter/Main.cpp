#include <iostream>
#include "GameManager.h"
#include "ResourseLoader.h"
#include "Player.h"
#include "Bullet.h"

int main()
{
	int win_width = 1600;
	int win_height = 900;
	RenderWindow window;
	window.create(VideoMode(win_width, win_height), "TopDownShooter");
	window.setVerticalSyncEnabled(true);

	GameManager* MGR = GameManager::GetInstance();
	ResourseLoader loader;

	Message* msg = new Message;
	msg->type = MsgType::Create;
	Player* p = new Player(loader.GetTextureByName("Actor.png"), { 400, 300 });
	msg->create.type = ObjType::Player;
	msg->create.new_object = p;
	MGR->SendMsg(msg);

	int cooldown = 0;
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

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (p->GetGameStatus()) window.close();
		}

		elapsed += clock.restart();
		if (elapsed.asMilliseconds() >= update_ms.asMilliseconds())
		{
			while (MGR->GetCountEnemy() < 10)
			{
				MGR->SpawnEnemy(p, loader, win_width, win_height);
			}
			elapsed -= update_ms;
		}

		if (elapsed.asMilliseconds() > update_ms.asMilliseconds() / 2.0f)
		{
			cooldown += 15;

			window.clear(Color(244, 164, 96, 255));
			MGR->Update(clock.restart().asSeconds());
			MGR->DrawObjects(window);

			if (Mouse::isButtonPressed(Mouse::Left) && cooldown >= 200)
			{
				MGR->SpawnBullet(p, loader);
				cooldown = 0;
			}
			/*if (!enemyList.empty()) for (auto enemy : enemyList)
			{
				window.draw(enemy->sprite);
				if (enemy->checkCollision(player)) player.deleted = true;
			}*/
			p->WatchTarget(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
			killsText.setString(to_string(killsPoints));
			window.draw(killsText);
			window.display();
		}
	}
	return 0;
}