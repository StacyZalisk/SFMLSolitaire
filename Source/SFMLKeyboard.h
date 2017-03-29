#ifndef SFMLKEYBOARD_H
#define SFMLKEYBOARD_H

class SFMLKeyboard
{
public:
	// Singleton get instance
	static SFMLKeyboard * GetInstance();
	// Update
	void Update();
	// Is key unpressed
	bool IsKeyUp(sf::Keyboard::Key key);
	// Is key pressed
	bool IsKeyDown(sf::Keyboard::Key key);
	// Was key JUST pressed
	bool IsKeyPressed(sf::Keyboard::Key key);
	// Was key JUST released
	bool IsKeyReleased(sf::Keyboard::Key key);

private:
	// Constructor
	SFMLKeyboard();
	// Singleton instance
	static SFMLKeyboard * Instance;
	// Keep track of previous information
	std::vector<bool> PreviousKeypresses;
	// Keep track of current information
	std::vector<bool> CurrentKeypresses;
};

#endif