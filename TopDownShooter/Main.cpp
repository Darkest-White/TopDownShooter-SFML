#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "ResourceManager.h"

int main()
{
	int win_width = 1200;
	int win_height = 600;
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

	Texture texture;
	texture.loadFromFile("Background.png");
	Sprite back;
	back.setTexture(texture);
	Text playButtonText;
	playButtonText.setFont(font);
	playButtonText.setString("Start");
	playButtonText.setCharacterSize(24);
	playButtonText.setPosition(350, 110);

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (MGR->GetGameStatus()) MGR->ResetGame();
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			if (playButtonText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				GameManager::GetInstance()->menu = false;
			}
		}

		if (!MGR->GetInstance()->GetMenuStatus())
		{
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
		else
		{
			window.draw(back);
			window.draw(playButtonText);
			window.display();
		}
	}
	return 0;
}