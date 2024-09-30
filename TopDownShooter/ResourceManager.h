#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
using namespace std;
using namespace sf;


class ResourceManager
{
private:
	static ResourceManager* instance;

	vector<pair<Texture, string>> textures;

	ResourceManager();
	~ResourceManager();

public:
	static ResourceManager* GetInstance();
	static void Destroy();

	void Load(string texture_name);
	Texture GetTextureByName(const string&);
};