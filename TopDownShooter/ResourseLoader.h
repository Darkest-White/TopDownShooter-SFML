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


class ResourseLoader
{
private:
	vector<pair<Texture, string>> allTexturesList;

public:
	ResourseLoader();
	~ResourseLoader();

	void Load(string);
	Texture GetTextureByName(const string&);
};