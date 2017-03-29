#ifndef MINIPLAYGAMEBUTTON_H
#define MINIPLAYGAMEBUTTON_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class MiniPlayGameButton;

class MiniPlayGameButton : public SFMLGameObject
{
public:

	//Returns the instance of the button
	static MiniPlayGameButton * GetPlayButton();

	~MiniPlayGameButton();

	void Display();

	virtual void Update(const sf::Time & DeltaTime);

private:
	static MiniPlayGameButton * Instance;

	MiniPlayGameButton();

};

#endif