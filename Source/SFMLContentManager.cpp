#include "stdafx.h"
#include "SFMLContentManager.h"

SFMLContentManager::SFMLContentManager()
	: TextureMap()
{
	// Nothing here...
}

SFMLContentManager::~SFMLContentManager()
{
	std::map<std::string, sf::Texture *>::iterator iter = TextureMap.begin();
	for( ; iter!=TextureMap.end(); ++iter )
	{
		delete iter->second;
	}
	TextureMap.clear();
}

sf::Texture * SFMLContentManager::LoadTexture(const std::string & resourceKey, const std::string & filename)
{
	std::map<std::string, sf::Texture *>::iterator iter = TextureMap.find(resourceKey);
	if (iter == TextureMap.end())
	{
		sf::Texture * texture = new sf::Texture();
		texture->loadFromFile(filename);
		TextureMap[resourceKey] = texture;
		return texture;
	}

	return iter->second;
}

sf::Texture * SFMLContentManager::GetTexture(const std::string & resourceKey)
{
	std::map<std::string, sf::Texture *>::iterator iter = TextureMap.find(resourceKey);
	return ( iter == TextureMap.end() ) ? nullptr : iter->second;
}