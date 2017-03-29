#include "stdafx.h"

#include <iostream>

#include "SFMLContentManager.h"
#include "SFMLGame.h"
#include "SFMLKeyboard.h"
#include "SFMLMouse.h"
#include "SFMLRoom.h"

SFMLGame *   SFMLGame::Instance(nullptr);
bool         SFMLGame::IsFixedTimeStep(true);

unsigned int SFMLGame::WindowWidth(1920);
unsigned int SFMLGame::WindowHeight(1080);
unsigned int SFMLGame::FPS(60);
bool         SFMLGame::IsFullscreen(true);
std::string  SFMLGame::TitleBar("");

SFMLGame::SFMLGame()
	: Window(new sf::RenderWindow()),
	  ContentManager( new SFMLContentManager() ),
	  CurrentRoom( nullptr ),
	  FrameDelay(),
	  NextRoom( nullptr ) 

{
	ResetWindow();
}

SFMLGame::~SFMLGame()
{
	delete Window;
}

void SFMLGame::EndGame()
{
	Window->close();
}

sf::RenderWindow * SFMLGame::GetWindow()
{
	return Window;
}

SFMLContentManager * SFMLGame::GetContentManager()
{
	return ContentManager;
}

void SFMLGame::ChangeRoom(SFMLRoom * TheNextRoom)
{
	// If two room changes occur in the same game cycle then
	// we must keep one and delete the other to avoid a memory leak
	if (NextRoom == nullptr)
	{
		NextRoom = TheNextRoom;
	}
	else
	{
		delete TheNextRoom;
	}
}

void SFMLGame::ResetWindow()
{
	int Style(sf::Style::Default);
	Style ^= (IsFullscreen) ? sf::Style::Fullscreen : sf::Style::None;
	Window->create(sf::VideoMode(WindowWidth, WindowHeight), TitleBar, Style);

	FrameDelay = sf::microseconds(1000000 / FPS);
}

SFMLGame * SFMLGame::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new SFMLGame();
	}

	return Instance;
}

void SFMLGame::MessageHandling()
{
	sf::Event Event;
	while (Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
}

void SFMLGame::Run( SFMLRoom * StartingRoom )
{
	// Avoid memory leaks
	if (CurrentRoom != nullptr)
	{
		delete CurrentRoom;
	}

	CurrentRoom = StartingRoom;
	
	sf::Clock Clock;
	sf::Time TimeSinceLastUpdate = sf::Time::Zero;
	while (Window->isOpen())
	{
		MessageHandling();

		sf::Time DeltaTime = Clock.restart();

		if (IsFixedTimeStep)
		{
			TimeSinceLastUpdate += DeltaTime;
			while (TimeSinceLastUpdate.asMicroseconds() > FrameDelay.asMicroseconds())
			{
				Update(TimeSinceLastUpdate);
				TimeSinceLastUpdate -= FrameDelay;
				// cout 
			}
		}
		else
		{
			Update(DeltaTime);
		}

		Draw();
	}
}

void SFMLGame::Update(const sf::Time & DeltaTime)
{
	SFMLKeyboard::GetInstance()->Update();
	SFMLMouse::GetInstance()->Update();

	NextRoom = nullptr;

	if (CurrentRoom != nullptr)
	{
		CurrentRoom->Update(DeltaTime);
	}

	if (NextRoom != nullptr)
	{
		delete CurrentRoom;
		CurrentRoom = NextRoom;
	}
}

void SFMLGame::Draw()
{
	Window->clear();

	if (CurrentRoom != nullptr)
	{
		CurrentRoom->Draw();
	}

	Window->display();
}

int SFMLGame::GetWindowWidth()
{
	return WindowWidth;
}

// Get screen height
int SFMLGame::GetWindowHeight()
{
	return WindowHeight;
}

SFMLRoom * SFMLGame::GetCurrentRoom()
{
	return CurrentRoom;
}