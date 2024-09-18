#include "ResourseLoader.h"

ResourseLoader::ResourseLoader()
{

}

ResourseLoader::~ResourseLoader()
{

}

Texture ResourseLoader::GetTextureByName(const string &textureName)
{
	auto it = find_if(allTexturesList.begin(), allTexturesList.end(),
		[&textureName](const pair<Texture, string>& element) { return element.second == textureName; });
	return it->first;
}

void ResourseLoader::Load(string textureName)
{
	Texture temp;
	temp.loadFromFile(textureName);
	allTexturesList.emplace_back(temp, textureName);
}