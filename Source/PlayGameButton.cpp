#include "stdafx.h"
#include "PlayGameButton.h"
#include "SolitaireGameRoom.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

PlayGameButton::PlayGameButton( float x, float y )
	: SFMLGameObject( "play", x, y, 2, 1 )
{
	// Nothing here...
}

void PlayGameButton::Update( const sf::Time & DeltaTime )
{
	GetSprite()->SetImageIndex(0);
	if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
	{
		GetSprite()->SetImageIndex(1);
		if(SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Button::Left) )
		{
			SFMLGame::GetInstance()->ChangeRoom( new SolitaireGameRoom() );
		}
	}
	
	SFMLGameObject::Update(DeltaTime);
}