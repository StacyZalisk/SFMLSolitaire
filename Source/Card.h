/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			Card.h
Version:			1.7

----------Description----------
The Card class is designed to represent a single card that 
would be found in a typical playing card deck.

----------Private Variables----------
char suit
Holds the card's suite value.  The character S is 
used to represent spades, the character C for clubs, D for
diamonds, and H for hearts

int value
Holds the card's face value.  An ace is represented by a 1, a
Jack by 11, Queen by 12, and King by 13.  All other values are
represented by their integer number equivilant.

float holdX
When a card is being moved, holdX retains the position of the
mouse on the card, allowing the card to be moved without 
adjusting the cursor's position on the card

float holdY
When a card is being moved, holdY retains the position of the
mouse on the card, allowing the card to be moved without
adjusting the cursor's position on the card

float previousX
Holds the x coordinate the card was at before it was moved.  
This exists so if a card is placed in an invalid location, it
can be moved back to its old locatoin.

float previousY
Holds the y coordinate the card was at before it was moved.
This exists so if a card is placed in an invalid location, it
can be moved back to its old locatoin.

bool moveable
Determines if the card can be moved or not

bool attached
When on a card stack, it tells whether or not is attached to
the card above it

bool begin
When the game has sat for 2 seconds, begin moving cards

bool isUp
Holds wether the card is face up or not

bool moving
Determines if the card is currently being moved or not

bool onTop
Determines if the card is on top of one of the card stacks
***************************************************************/

#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

#include <string>

class Card : public SFMLGameObject
{
public:
	Card(std::string name, float x, float y, int framesH, int framesV, char s, int val, bool can_move = false, bool is_attached = false,
		bool can_begin = false, bool is_up = false, bool is_moving = false, bool on_top = false);

	virtual void Update( const sf::Time & DeltaTime );

	//Returns the card's suite
	char getSuit() { return suit; }

	//Returns the card's face value
	int getFaceValue() { return value; }

	//Returns the color of the card
	char getColor() { return color; }

	//Sets whether the card can be moved or not
	void setMoveable(bool status) { moveable = status; }
	//Returns whether or not the card can be moved
	bool isMoveable() { return moveable; }

	//Sets whether the card is attached to the card above it
	void setAttached(bool status) { attached = status; }
	//Returns whether or not the card is attached to the card above it
	bool isAttached() { return attached; }

	//Sets if the card is face up or not
	void setFaceUp(bool status) { isUp = status; }
	//Returns whether the card is face up or not
	bool isFaceUp() { return isUp; }

	//Sets if the card is on top of a stack or not
	void setOnTop(bool status) { onTop = status; }
	//Returns if the card is on the top of a stack or not
	bool isOnTop() { return onTop; }

	//Returns the previous X position
	float getPreviousX() { return previousX; }

	//Returns the previous Y position
	float getPreviousY() { return previousY; }

	//Returns the card's hold x position
	float getHoldX() { return holdX; }

	//Returns if the card is moving or not
	bool isMoving() { return moving; }

	//Returns true if the card is placed on a stack
	bool isOverStack();
	//Returns true if the card is placed on a upper card slot
	bool isOverSlots();

	//Handles alarms
	virtual void OnVariableAlarm(int AlarmNumber);

	//Returns the card to its natural resting position
	void returnCard();

	//Sets the cards resting position
	void setRestingPosition(float x, float y);

	//Overloaded operators
	bool operator ==(Card * card2);
	bool operator !=(Card * card2);

private:
	//Holds the card's suit
	char suit;
	//Holds the card's face value
	int value;
	//Holds the card's color
	char color;

	//Holds the x position of the mouse on the card
	float holdX;
	//Holds the y position of the mouse on the card
	float holdY;

	//Holds the last x position when the card was at rest
	float previousX;
	//Holds the last y position when the card was at rest
	float previousY;

	//Determines whether or not the card can be moved
	bool moveable;

	//Determines whether or not the card is attached to its above card
	bool attached;

	//Determines if cards can move or not
	bool begin;

	//Determines if the card is face up or not
	bool isUp;

	//Determines if the card is moving or not
	bool moving;

	//Determines if the card is on top of one of the card stacks
	bool onTop;
};

#endif