#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
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

	void Load(string texture_name);
	Texture GetTextureByName(const string&);
};