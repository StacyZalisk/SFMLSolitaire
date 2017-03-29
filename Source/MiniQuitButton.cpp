#include "stdafx.h"
#include "MiniQuitButton.h"
#include "SolitaireGameRoom.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

MiniQuitButton * MiniQuitButton::Instance(nullptr);

/***************************************************************
Returns the instance of the button
***************************************************************/
MiniQuitButton * MiniQuitButton::GetQuitButton()
{
	if (Instance == nullptr)
	{
		Instance = new MiniQuitButton();
	}

	return Instance;
}

MiniQuitButton::MiniQuitButton()
: SFMLGameObject("miniQuit", 560, 424, 2, 1)
{
	GetSprite()->SetPerformCollisionDetection(false);
	GetSprite()->SetVisible(false);
	SetDepth(101);
}

MiniQuitButton::~MiniQuitButton()
{
	Instance = NULL;
}

void MiniQuitButton::Update(const sf::Time & DeltaTime)
{
	SFMLGameObject::Update(DeltaTime);

	if (GetSprite()->Visible())
	{
		GetSprite()->SetImageIndex(0);
		if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
		{
			GetSprite()->SetImageIndex(1);
			if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Button::Left))
			{
				SFMLGame::GetInstance()->EndGame();
			}
		}
	}
}

void MiniQuitButton::Display()
{
	GetSprite()->SetVisible(true);
}