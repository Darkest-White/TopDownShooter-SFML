#include<iostream>
#include<SFML\Graphics.hpp>
using namespace std;
using namespace sf;


Event ev;

int main()
{
	RenderWindow win(VideoMode(1280, 720), "TopDownShooter");

	while (win.isOpen())
	{
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
			}
		}

		win.clear();
		//win.draw();
		win.display();
	}
}