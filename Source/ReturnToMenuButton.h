#ifndef RETURNTOMENUBUTTON_H
#define RETURNTOMENUBUTTON_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class ReturnToMenuButton : public SFMLGameObject
{
public:
	ReturnToMenuButton(float x, float y);

	virtual void Update( const sf::Time & DeltaTime );
};

#endif