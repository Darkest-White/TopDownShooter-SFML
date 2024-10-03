#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
	Load("Actor.png");
	Load("Bullet.png");
	Load("Background.png");
}

ResourceManager::~ResourceManager()
{
	textures.clear();
}

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == nullptr) instance = new ResourceManager();
	return instance;
}

void ResourceManager::Destroy()
{
	if (instance) delete instance;
	instance = nullptr;
}

Texture ResourceManager::GetTextureByName(const string &textureName)
{
	auto it = find_if(textures.begin(), textures.end(),
		[&textureName](const pair<Texture, string>& element) { return element.second == textureName; });
	return it->first;
}

void ResourceManager::Load(string texture_name)
{
	Texture temp;
	temp.loadFromFile(texture_name);
	textures.emplace_back(temp, texture_name);
}