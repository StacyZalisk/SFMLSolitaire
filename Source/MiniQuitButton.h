#ifndef MINIQUITBUTTON_H
#define MINIQUITBUTTON_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class MiniQuitButton;

class MiniQuitButton : public SFMLGameObject
{
public:

	//Returns the instance of the button
	static MiniQuitButton * GetQuitButton();

	~MiniQuitButton();

	void Display();

	virtual void Update(const sf::Time & DeltaTime);

private:
	static MiniQuitButton * Instance;

	MiniQuitButton();

};

#endif