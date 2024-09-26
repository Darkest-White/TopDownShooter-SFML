#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
using namespace std;
using namespace sf;


class ResourseManager
{
private:
	static ResourseManager* instance;

	vector<pair<Texture, string>> textures;

	ResourseManager();
	~ResourseManager();

public:
	static ResourseManager* GetInstance();
	static void Destroy();

	void Load(string texture_name);
	Texture GetTextureByName(const string&);
};