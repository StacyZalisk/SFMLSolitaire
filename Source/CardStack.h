/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/15/2015
Last Updated On:	5/9/2015
File Name:			CardStack.h
Version:			1.7

----------Description----------
The CardStack is used to hold the seven stacks of cards used to
move and hold the cards in Solitaire.

----------Private Variables----------
std::vector<Card *> stack[1-7]
Holds one stack of cards
***************************************************************/

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <SFML/Graphics.hpp>
#include "Card.h"

#include <vector>
#include <string>

class CardStack;
class SFMLGameObject;

class CardStack : public SFMLGameObject
{
public:
	//Updates the CardStack
	virtual void Update(const sf::Time & DeltaTime);

	//Returns the instance of the card stack
	static CardStack * GetCardStack();

	//Descructor
	~CardStack();

	//Adds a card to the stack
	void addToStack(Card * card);
	void addToStack(Card * card, int stackNumber);
	void addToFirstStack(Card * card, int stackNumber);

	//Returns whether or not the card is in the card stacks
	bool isInStack(Card * card);

	//Returns the number of the stack the card is on
	int inWhatStack(Card * card);

	//Removes the card from the selected stack
	void removeFromStack(int stackNumber);

	//Freezes all cards in the cardStacks, except for the provided card
	void freezeStacks(Card * card);

	//Resets the card stacks
	void resetStacks();

	//Moves cards attached to each other
	void moveAttached(Card * card);

	//Returns a stack of attached cards to their resting position
	void returnAttached(Card * card);

	//Adds a series of attached cards to a stack
	void addAttached(Card * card, int stackNum);

	//Sets up the card stacks after the first deal
	void setFirstRound();

	//Sets the back card in the specified stack as attached
	void attachBack(int stackNum);

private:
	//Constructor
	CardStack();
	//Holds the instance of the card stacks
	static CardStack * Instance;

	//Holds the seven stacks of cards
	std::vector<Card *> stack1;
	std::vector<Card *> stack2;
	std::vector<Card *> stack3;
	std::vector<Card *> stack4;
	std::vector<Card *> stack5;
	std::vector<Card *> stack6;
	std::vector<Card *> stack7;
};

#endif