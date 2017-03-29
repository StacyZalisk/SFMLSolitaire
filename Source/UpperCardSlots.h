/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/23/2015
Last Updated On:	5/9/2015
File Name:			UpperCardSlots.h
Version:			1.7

----------Description----------
The Upper Card Slots hold the four stacks of cards based on their
matching suits.  If all the cards are placed in the upper card 
slots in the proper order, the game is won

----------Private Variables----------
std::vector<Card *> heartStack
Holds the stack of heart cards

std::vector<Card *> diamondStack
Holds the stack of diamond cards

std::vector<Card *> clubStack
Holds the stack of club cards

std::vector<Card *> spadeStack
Holds the stack of spade cards
***************************************************************/

#ifndef UPPERCARDSLOTS_H
#define UPPERCARDSLOTS_H

#include <SFML/Graphics.hpp>
#include "Card.h"

#include <vector>
#include <string>

class UpperCardSlots;
class SFMLGameObject;

class UpperCardSlots : public SFMLGameObject
{
public:
	//Updates the CardStack
	virtual void Update(const sf::Time & DeltaTime);

	//Returns the instance of the card stack
	static UpperCardSlots * GetUpperCardSlots();

	//Descructor
	~UpperCardSlots();

	//Adds a card to the stack
	void addToSlots(Card * card);

	//Adds the card to the specified stack
	void addToSlots(Card * card, int position);

	//Resets the cards on the slots
	void resetSlots();

	//Displays the win dialog box
	void displayWinInfo();

private:
	//Constructor
	UpperCardSlots();
	//Holds the instance of the card stacks
	static UpperCardSlots * Instance;

	//Holds the seven stacks of cards
	std::vector<Card *> heartStack;
	std::vector<Card *> clubStack;
	std::vector<Card *> diamondStack;
	std::vector<Card *> spadeStack;
};

#endif