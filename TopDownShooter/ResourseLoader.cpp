#include "ResourseLoader.h"



ResourseLoader::ResourseLoader()
{

}


Texture ResourseLoader::getTextureByName(const string &textureName)
{
	auto it = find_if(allTexturesList.begin(), allTexturesList.end(),
		[&textureName](const pair<Texture, string>& element) { return element.second == textureName; });
	return it->first;
}

void ResourseLoader::load(string textureName)
{
	Texture temp;
	temp.loadFromFile(textureName);
	allTexturesList.emplace_back(temp, textureName);
}

ResourseLoader::~ResourseLoader()
{
}