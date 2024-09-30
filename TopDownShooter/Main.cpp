#include <iostream>
#include "GameManager.h"
#include "Player.h"

int main()
{
	int win_width = 1600;
	int win_height = 800;
	RenderWindow window;
	window.create(VideoMode(win_width, win_height), "TopDownShooter");
	window.setVerticalSyncEnabled(true);

	GameManager* MGR = GameManager::GetInstance();

	MGR->SpawnPlayer(300, 400);

	int cooldown = 0;

	Font font;
	font.loadFromFile("Skramp.ttf");
	Text killsText;
	killsText.setFont(font);
	killsText.setFillColor(Color::Black);
	killsText.setCharacterSize(20);

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (MGR->GetGameStatus()) window.close();
		}

		while (MGR->GetCountEnemy() < 10)
		{
			MGR->SpawnEnemy(MGR->GetPlayer(), win_width, win_height);
		}

		window.clear(Color(244, 164, 96, 255));
		MGR->Update(clock.restart().asSeconds());
		MGR->DrawObjects(window);

		cooldown += 15;
		if (Mouse::isButtonPressed(Mouse::Left) && cooldown >= 200)
		{
			MGR->SpawnBullet(MGR->GetPlayer());
			cooldown = 0;
		}

		killsText.setString("Score " + to_string(MGR->GetScore()));

		MGR->GetPlayer()->WatchTarget(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		window.draw(killsText);
		window.display();
	}
	return 0;
}