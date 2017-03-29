#include "stdafx.h"
#include "ReturnToMenuButton.h"
#include "MainMenuRoom.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

ReturnToMenuButton::ReturnToMenuButton(float x, float y)
	: SFMLGameObject( "return", x, y, 2, 1 )
{
	// Nothing here...
}

void ReturnToMenuButton::Update(const sf::Time & DeltaTime)
{
	GetSprite()->SetImageIndex(0);
	if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
	{
		GetSprite()->SetImageIndex(1);
		if(SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Button::Left) )
		{
			SFMLGame::GetInstance()->ChangeRoom( new MainMenuRoom() );
		}
	}
	
	SFMLGameObject::Update(DeltaTime);
}