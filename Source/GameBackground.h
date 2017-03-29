#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class GameBackground : public SFMLGameObject
{
public:
	GameBackground(float x, float y);
};

#endif