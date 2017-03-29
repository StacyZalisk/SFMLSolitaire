#include "stdafx.h"
#include "MiniPlayGameButton.h"
#include "MainMenuRoom.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

MiniPlayGameButton * MiniPlayGameButton::Instance(nullptr);

/***************************************************************
Returns the instance of the button
***************************************************************/
MiniPlayGameButton * MiniPlayGameButton::GetPlayButton()
{
	if (Instance == nullptr)
	{
		Instance = new MiniPlayGameButton();
	}

	return Instance;
}

MiniPlayGameButton::MiniPlayGameButton()
: SFMLGameObject("miniNew", 560, 334, 2, 1)
{
	GetSprite()->SetPerformCollisionDetection(false);
	GetSprite()->SetVisible(false);
	SetDepth(100);
}

MiniPlayGameButton::~MiniPlayGameButton()
{
	Instance = NULL;
}

void MiniPlayGameButton::Display()
{
	GetSprite()->SetVisible(true);
}

void MiniPlayGameButton::Update(const sf::Time & DeltaTime)
{
	if (GetSprite()->Visible())
	{
		GetSprite()->SetImageIndex(0);
		if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
		{
			GetSprite()->SetImageIndex(1);
			if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Button::Left))
			{
				SFMLGame::GetInstance()->ChangeRoom(new MainMenuRoom());
			}
		}
	}

	SFMLGameObject::Update(DeltaTime);
}