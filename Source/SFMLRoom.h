#ifndef SFMLROOM_H
#define SFMLROOM_H

#include <vector>
#include <SFML/Graphics.hpp>

class SFMLGameObject;
class SFMLSprite;

class SFMLRoom
{
public:
	// Constructor
	SFMLRoom();
	// Destructor
	virtual ~SFMLRoom();
	// Update the room
	virtual void Update(const sf::Time & DeltaTime);
	// Draw the room
	virtual void Draw();
	// Create an object
	void InstanceCreate(SFMLGameObject * Object);
	// Create an object
	void InstanceDestroy(SFMLGameObject * Object);
	// Test for collision
	void PerformCollisionDetection(SFMLGameObject * ObjectToTest);

	void DrawText( float x, float y, const std::string & phrase, float xscale=1, float yscale=1, sf::Color color=sf::Color::White, const std::string &fontfile="ascii" );

	template<class T>
	std::vector<T *> GetGameObjectsOfType();

	template<class T>
	T * GetFirstGameObjectOfType();

	std::vector<SFMLGameObject *> GetGameObjectsAtPoint( float x, float y );

private:
	// Vector of game objects to maintain
	std::vector<SFMLGameObject *> GameObjects;

	// Vector of created game objects to maintain
	std::vector<SFMLGameObject *> CreatedGameObjects;

	SFMLSprite * Font;
};

template<class T>
std::vector<T *> SFMLRoom::GetGameObjectsOfType()
{
	std::vector<T *> a;

	for (SFMLGameObject * t : GameObjects)
	{
		T * rrr = dynamic_cast<T *>(t);
		if (rrr != nullptr)
		{
			a.push_back(rrr);
		}
	}

	return a;
}

template<class T>
T * SFMLRoom::GetFirstGameObjectOfType()
{
	for (SFMLGameObject * t : GameObjects)
	{
		T * rrr = dynamic_cast<T *>(t);
		if (rrr != nullptr)
		{
			return rrr;
		}
	}

	return nullptr;
}

#endif