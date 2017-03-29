#ifndef CONTENT_MANAGER_H
#define CONTENT_MANAGER_H

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
class SFMLContentManager
{
public:
	SFMLContentManager();
	~SFMLContentManager();

	sf::Texture * LoadTexture(const std::string & resourceKey, const std::string & filename);
	sf::Texture * GetTexture(const std::string & resourceKey);

private:
	std::map<std::string, sf::Texture *> TextureMap;
};

#endif