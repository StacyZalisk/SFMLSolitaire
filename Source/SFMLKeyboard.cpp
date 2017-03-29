#include "stdafx.h"
#include "SFMLKeyboard.h"

SFMLKeyboard * SFMLKeyboard::Instance(nullptr);

SFMLKeyboard::SFMLKeyboard()
{
	for (int i = 0; i < 200; ++i)
	{
		PreviousKeypresses.push_back(false);
		CurrentKeypresses.push_back(false);
	}
}

SFMLKeyboard * SFMLKeyboard::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new SFMLKeyboard();
	}

	return Instance;
}

bool SFMLKeyboard::IsKeyUp(sf::Keyboard::Key key)
{
	return (CurrentKeypresses[key] == false);
}

bool SFMLKeyboard::IsKeyDown(sf::Keyboard::Key key)
{
	return (CurrentKeypresses[key] == true);
}

bool SFMLKeyboard::IsKeyPressed(sf::Keyboard::Key key)
{
	return ((CurrentKeypresses[key] == true) && (PreviousKeypresses[key] == false));
}

bool SFMLKeyboard::IsKeyReleased(sf::Keyboard::Key key)
{
	return ((CurrentKeypresses[key] == false) && (PreviousKeypresses[key] == true));
}

void SFMLKeyboard::Update()
{
	// Set the previous state
	PreviousKeypresses = CurrentKeypresses;

	// Update current state
	for (int i = 0; i < 200; ++i)
	{
		CurrentKeypresses[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
	}
}