#include<iostream>
#include<SFML\Graphics.hpp>
using namespace std;
using namespace sf;


int win_width = 1280;
int win_height = 720;
Event ev;
Clock clk;
float current_frame = 0;


class Player
{
private:

public:

	float x, y, w, h, speed = 0;
	int dir = 0;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String f, int x, int y, float w, float h)
	{
		file = f;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		image.loadFromFile("img/" + f);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	void update(float time)
	{
		switch (dir)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
};


int main()
{
	RenderWindow win(VideoMode(win_width, win_height), "TopDownShooter");

	float time = clk.getElapsedTime().asMilliseconds();
	clk.restart();
	time = time / 800;
	
	float hero_speed = 0.5;

	Image hero_image;
	hero_image.loadFromFile("img/hero/hero.png");

	Texture hero_texture;
	hero_texture.loadFromImage(hero_image);

	Sprite hero_sprite;
	hero_sprite.setTexture(hero_texture);
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
			hero_sprite.setRotation(-90);
			hero_sprite.move(0, -hero_speed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			hero_sprite.setRotation(90);
			hero_sprite.move(0, hero_speed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			hero_sprite.setRotation(180);
			hero_sprite.move(-hero_speed * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			hero_sprite.setRotation(0);
			hero_sprite.move(hero_speed * time, 0);
		}

		cout << time << endl;

		win.clear();
		win.draw(hero_sprite);
		win.display();
	}
}