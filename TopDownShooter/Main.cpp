#include <iostream>
#include "GameManager.h"
#include "ResourseManager.h"
#include "Player.h"

int main()
{
	int win_width = 1600;
	int win_height = 900;
	RenderWindow window;
	window.create(VideoMode(win_width, win_height), "TopDownShooter");
	window.setVerticalSyncEnabled(true);

	GameManager* MGR = GameManager::GetInstance();
	ResourseManager* RSR = ResourseManager::GetInstance();

	MGR->SpawnPlayer(300, 400, RSR->GetInstance());

	int cooldown = 0;
	/*int killsPoints = 0;

	Font font;
	font.loadFromFile("Skramp.ttf");
	Text killsText;
	killsText.setFont(font);
	killsText.setFillColor(Color::Black);
	killsText.setString(to_string(killsPoints));
	killsText.setCharacterSize(20);*/

	Clock clock;
	Time elapsed = clock.restart();
	const Time update_ms = milliseconds(30.0f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (MGR->GetGameStatus()) window.close();
		}

		elapsed += clock.restart();

		if (elapsed.asMilliseconds() >= update_ms.asMilliseconds())
		{
			while (MGR->GetCountEnemy() < 10)
			{
				MGR->SpawnEnemy(MGR->GetPlayer(), RSR->GetInstance(), win_width, win_height);
			}
			elapsed -= update_ms;
		}

		if (elapsed.asMilliseconds() > update_ms.asMilliseconds() / 2)
		{
			cooldown += 15;

			window.clear(Color(244, 164, 96, 255));
			MGR->Update(clock.restart().asSeconds());
			MGR->DrawObjects(window);

			if (Mouse::isButtonPressed(Mouse::Left) && cooldown >= 200)
			{
				MGR->SpawnBullet(MGR->GetPlayer(), RSR->GetInstance());
				cooldown = 0;
			}


			MGR->GetPlayer()->WatchTarget(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
			//killsText.setString(to_string(killsPoints));
			//window.draw(killsText);
			window.display();
		}
	}
	return 0;
}