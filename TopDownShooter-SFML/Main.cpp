#include<iostream>
#include<SFML\Graphics.hpp>
using namespace std;
using namespace sf;


int win_width = 1280;
int win_height = 720;
Event ev;
Clock clk;
float current_frame = 0;


int main()
{
	RenderWindow win(VideoMode(win_width, win_height), "TopDownShooter");

	float time = clk.getElapsedTime().asMilliseconds();
	clk.restart();
	time = time / 800;
	
	float hero_speed = 0.5;

	Image hero_image_1;
	hero_image_1.loadFromFile("img/hero/hero_1.png");
	Image hero_image_2;
	hero_image_2.loadFromFile("img/hero/hero_2.png");

	Texture hero_texture_1;
	hero_texture_1.loadFromImage(hero_image_1);
	Texture hero_texture_2;
	hero_texture_2.loadFromImage(hero_image_2);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture_1);
	hero_sprite.setTextureRect(IntRect(0, 0, 313, 207));
	hero_sprite.setOrigin(313 / 2, 207 / 2);
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
			current_frame += 0.005 * time;
			if (current_frame > 3) current_frame = 0;

			hero_sprite.setTexture(hero_texture_2);
			hero_sprite.setTextureRect(IntRect(int(current_frame), 0, 207, 313));
			hero_sprite.setOrigin(207 / 2, 313 / 2);
			hero_sprite.move(0, -hero_speed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			hero_sprite.setTexture(hero_texture_2);
			hero_sprite.setTextureRect(IntRect(207, 313, -207, -313));
			hero_sprite.setOrigin(207 / 2, 313 / 2);
			hero_sprite.move(0, hero_speed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			hero_sprite.setTexture(hero_texture_1);
			hero_sprite.setTextureRect(IntRect(313, 207, -313, -207));
			hero_sprite.setOrigin(313 / 2, 207 / 2);
			hero_sprite.move(-hero_speed * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			hero_sprite.setTexture(hero_texture_1);
			hero_sprite.setTextureRect(IntRect(0, 0, 313, 207));
			hero_sprite.setOrigin(313 / 2, 207 / 2);
			hero_sprite.move(hero_speed * time, 0);
		}

		cout << time << endl;

		win.clear();
		win.draw(hero_sprite);
		win.display();
	}
}