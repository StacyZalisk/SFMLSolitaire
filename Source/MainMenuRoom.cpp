#include "stdafx.h"
#include "MainMenuBackground.h"
#include "MainMenuRoom.h"
#include "PlayGameButton.h"
#include "QuitGameButton.h"
#include "SFMLContentManager.h"
#include "SFMLGame.h"

MainMenuRoom::MainMenuRoom()
{
	// Load all assets into the content manager
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("menu", "graphics/menuBackground.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("play", "graphics/playGame.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("quit", "graphics/quitGame.png");

	// Create objects that start the room running
	InstanceCreate( new MainMenuBackground( 0, 0 ) );
	InstanceCreate( new PlayGameButton( 438, 238 ) );
	InstanceCreate( new QuitGameButton( 438, 438 ) );
}