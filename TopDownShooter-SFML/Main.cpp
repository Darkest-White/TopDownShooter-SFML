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

	float x, y, dx, dy, w, h, speed = 0;
	int dir = 0;
	string file;

	Image image;
	Texture texture;

	Sprite sprite;

	Player(string f, int x, int y, float w, float h)
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
		sprite.setOrigin(w / 2, h / 2);
		sprite.setPosition(x, y);
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0:
			dx = dy = 0;
			break;

		case 1:
			dx = speed;
			dy = 0;
			sprite.setRotation(0);
			break;

		case 2:
			dx = -speed;
			dy = 0;
			sprite.setRotation(180);
			break;

		case 3:
			dy = speed;
			dx = 0;
			sprite.setRotation(90);
			break;

		case 4:
			dy = -speed;
			dx = 0;
			sprite.setRotation(-90);
			break;

		default:
			dx = dy = 0;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
	}
};


int main()
{
	RenderWindow win(VideoMode(win_width, win_height), "TopDownShooter");

	Player p("hero/hero.png", win_width / 2, win_height / 2, 313, 206);

	float time = clk.getElapsedTime().asMilliseconds();
	clk.restart();
	time = time / 800;

	float current_frame = 0;

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
			p.dir = 4;
			p.speed = 0.5;

			current_frame += 0.005 * time;
			if (current_frame > 3) current_frame = 0;
			p.sprite.setTextureRect(IntRect(313 * int(current_frame), 206 * int(current_frame), 313, 206));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			p.dir = 3;
			p.speed = 0.5;
			current_frame += 0.005 * time;
			if (current_frame > 3) current_frame = 0;
			p.sprite.setTextureRect(IntRect(313 * int(current_frame), 206 * int(current_frame), 313, 206));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			p.dir = 2;
			p.speed = 0.5;
			current_frame += 0.005 * time;
			if (current_frame > 3) current_frame = 0;
			p.sprite.setTextureRect(IntRect(313 * int(current_frame), 206 * int(current_frame), 313, 206));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			p.dir = 1;
			p.speed = 0.5;
			current_frame += 0.005 * time;
			if (current_frame > 3) current_frame = 0;
			p.sprite.setTextureRect(IntRect(313 * int(current_frame), 206 * int(current_frame), 313, 206));
		}


		win.clear();
		p.update(time);
		win.draw(p.sprite);
		win.display();
	}
}