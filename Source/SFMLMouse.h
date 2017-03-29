#ifndef SFMLMOUSE_H
#define SFMLMOUSE_H

class SFMLMouse
{
public:
	// Singleton get instance
	static SFMLMouse * GetInstance();
	// Update
	void Update();

	sf::Vector2i GetPosition();
	void SetPosition( const sf::Vector2i & position );
	
	// Is button unpressed
	bool IsButtonUp(sf::Mouse::Button button);
	// Is button pressed
	bool IsButtonDown(sf::Mouse::Button button);
	// Was button JUST pressed
	bool IsButtonPressed(sf::Mouse::Button button);
	// Was button JUST released
	bool IsButtonReleased(sf::Mouse::Button button);

private:
	// Constructor
	SFMLMouse();
	// Singleton instance
	static SFMLMouse * Instance;
	// Keep track of previous information
	std::vector<bool> PreviousMousePresses;
	// Keep track of current information
	std::vector<bool> CurrentMousePresses;
};

#endif