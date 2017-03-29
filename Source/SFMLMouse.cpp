#include "stdafx.h"
#include "SFMLMouse.h"

SFMLMouse * SFMLMouse::Instance(nullptr);

SFMLMouse::SFMLMouse()
{
	for (int i = 0; i < 5; ++i)
	{
		PreviousMousePresses.push_back(false);
		CurrentMousePresses.push_back(false);
	}
}

SFMLMouse * SFMLMouse::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new SFMLMouse();
	}

	return Instance;
}

sf::Vector2i SFMLMouse::GetPosition()
{
	return sf::Mouse::getPosition();
}

void SFMLMouse::SetPosition(const sf::Vector2i & position)
{
	sf::Mouse::setPosition(position);
}

void SFMLMouse::Update()
{
	// Update previous state
	PreviousMousePresses = CurrentMousePresses;

	// Update current state
	for (int i = 0; i < 5; ++i)
	{
		CurrentMousePresses[i] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));
	}
}

bool SFMLMouse::IsButtonUp(sf::Mouse::Button button)
{
	return (CurrentMousePresses[button] == false);
}

bool SFMLMouse::IsButtonDown(sf::Mouse::Button button)
{
	return (CurrentMousePresses[button] == true);
}

bool SFMLMouse::IsButtonPressed(sf::Mouse::Button button)
{
	return ((CurrentMousePresses[button] == true) && (PreviousMousePresses[button] == false));
}

bool SFMLMouse::IsButtonReleased(sf::Mouse::Button button)
{
	return ((CurrentMousePresses[button] == false) && (PreviousMousePresses[button] == true));
}