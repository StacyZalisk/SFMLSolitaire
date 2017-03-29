#include "stdafx.h"
#include "QuitGameButton.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

QuitGameButton::QuitGameButton( float x, float y )
	: SFMLGameObject( "quit", x, y, 2, 1 )
{
	// Nothing here...
}

void QuitGameButton::Update( const sf::Time & DeltaTime )
{
	SFMLGameObject::Update(DeltaTime);

	GetSprite()->SetImageIndex(0);
	if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
	{
		GetSprite()->SetImageIndex(1);
		if(SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Button::Left) )
		{
			SFMLGame::GetInstance()->EndGame();
		}
	}
}