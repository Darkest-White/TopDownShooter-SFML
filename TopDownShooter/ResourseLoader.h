#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include <string>
#include <string>
#include <sstream>
#include <vector>
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
	void load(string);
	Texture getTextureByName(const string&);
	~ResourseLoader();
};