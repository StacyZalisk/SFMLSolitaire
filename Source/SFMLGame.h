#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <SFML/Graphics.hpp>

class SFMLContentManager;
class SFMLRoom;

// ------------------
// Use as a singleton
// ------------------
class SFMLGame
{
public:
	// Destructor
	virtual ~SFMLGame();
	// Get singleton instance
	static SFMLGame * GetInstance();
	// Run the main game loop
	virtual void Run( SFMLRoom * StartingRoom );
	// Handle OS messages
	virtual void MessageHandling();
	// Update the game
	virtual void Update(const sf::Time & DeltaTime);
	// Draw the game
	virtual void Draw();
	// Get the render window
	sf::RenderWindow * GetWindow();
	// Get the content manager
	SFMLContentManager * GetContentManager();
	// Reset the render window
	void ResetWindow();
	// Change the current room
	void ChangeRoom(SFMLRoom * NextRoom);
	// Get screen width
	static int GetWindowWidth();
	// Get screen height
	static int GetWindowHeight();
	// Get current room
	SFMLRoom * GetCurrentRoom();
	// End game
	void EndGame();

private:
	// Constructor
	SFMLGame();
	// Singleton instance
	static SFMLGame * Instance;
	// Render window
	sf::RenderWindow * Window;
	// The content manager
	SFMLContentManager * ContentManager;
	// The current room in play
	SFMLRoom * CurrentRoom;
	// Width of the render window
	static unsigned int WindowWidth;
	// Height of the render window
	static unsigned int WindowHeight;
	// Maintain how long to wait between game frames
	sf::Time FrameDelay;
	// Next room
	SFMLRoom * NextRoom;
	// Is the game in fixed or variable time mode
	static bool IsFixedTimeStep;
	// How many frames per second are we trying to run at
	static unsigned int FPS;
	// Is the game running fullscreen
	static bool IsFullscreen;
	// Title bar for the render window
	static std::string TitleBar;
};

#endif