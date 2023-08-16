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
	Image hero_image_2;
	hero_image_2.loadFromFile("img/hero_2.png");

	Texture hero_texture;
	hero_texture.loadFromImage(hero_image);
	Texture hero_texture_2;
	hero_texture_2.loadFromImage(hero_image_2);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setTextureRect(IntRect(0, 0, 313, 207));
	//hero_sprite.setOrigin(313 / 2, 207 / 2);
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

		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			hero_sprite.move(0, -0.1);
			hero_sprite.setTexture(hero_texture_2);
			hero_sprite.setTextureRect(IntRect(0, 313, 207, -313));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			hero_sprite.move(0, 0.1);
			hero_sprite.setTexture(hero_texture_2);
			hero_sprite.setTextureRect(IntRect(0, 0, 207, 313));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			hero_sprite.move(-0.1, 0);
			hero_sprite.setTexture(hero_texture);
			hero_sprite.setTextureRect(IntRect(313, 0, -313, 207));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			hero_sprite.move(0.1, 0);
			hero_sprite.setTexture(hero_texture);
			hero_sprite.setTextureRect(IntRect(0, 0, 313, 207));
		}


		win.clear();
		win.draw(hero_sprite);
		win.display();
	}
}