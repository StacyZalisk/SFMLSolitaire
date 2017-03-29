#ifndef PLAYGAMEBUTTON_H
#define PLAYGAMEBUTTON_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class PlayGameButton : public SFMLGameObject
{
public:
	PlayGameButton( float x, float y );

	virtual void Update( const sf::Time & DeltaTime );
};

#endif