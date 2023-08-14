#include<iostream>
#include<SFML\Graphics.hpp>
using namespace std;
using namespace sf;


int win_width = 1280;
int win_height = 720;
Event ev;

int main()
{
	RenderWindow win(VideoMode(win_width, win_height), "TopDownShooter");

	Image hero_image;
	hero_image.loadFromFile("img/hero.png");

	Texture hero_texture;
	hero_texture.loadFromImage(hero_image);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setTextureRect(IntRect(0, 0, 313, 207));
	hero_sprite.setPosition(win_width / 2, win_height / 2);

	while (win.isOpen())
	{
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) { hero_sprite.move(0, -1); }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { hero_sprite.move(0, 1); }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { hero_sprite.move(-1, 0); }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { hero_sprite.move(1, 0); }

		win.clear();
		win.draw(hero_sprite);
		win.display();
	}
}