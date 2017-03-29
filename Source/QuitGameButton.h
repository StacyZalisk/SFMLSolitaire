#ifndef QUITGAMEBUTTON_H
#define QUITGAMEBUTTON_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class QuitGameButton : public SFMLGameObject
{
public:
	QuitGameButton( float x, float y );

	virtual void Update( const sf::Time & DeltaTime );
};

#endif