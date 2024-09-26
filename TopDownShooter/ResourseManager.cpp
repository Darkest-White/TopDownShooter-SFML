#include "ResourseManager.h"

ResourseManager* ResourseManager::instance = nullptr;

ResourseManager::ResourseManager()
{
	Load("Actor.png");
	Load("Bullet.png");
	Load("NoTexture.png");
}

ResourseManager::~ResourseManager()
{
	textures.clear();
}

ResourseManager* ResourseManager::GetInstance()
{
	if (instance == nullptr) instance = new ResourseManager();
	return instance;
}

void ResourseManager::Destroy()
{
	if (instance) delete instance;
	instance = nullptr;
}

Texture ResourseManager::GetTextureByName(const string &textureName)
{
	auto it = find_if(textures.begin(), textures.end(),
		[&textureName](const pair<Texture, string>& element) { return element.second == textureName; });
	return it->first;
}

void ResourseManager::Load(string texture_name)
{
	Texture temp;
	temp.loadFromFile(texture_name);
	textures.emplace_back(temp, texture_name);
}