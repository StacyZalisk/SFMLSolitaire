/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			Card.cpp
Version:			1.7

----------Description----------
The Card class is designed to represent a single card that
would be found in a typical playing card deck.
***************************************************************/

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "CardStack.h"
#include "UpperCardSlots.h"
#include "SFMLSprite.h"
#include "SFMLMouse.h"

/***************************************************************
Card constructor
***************************************************************/
Card::Card(std::string name, float x, float y, int framesH, int framesV, char s, int val, bool can_move, bool is_attached,
	bool can_begin, bool is_up, bool is_moving, bool on_top)
	: SFMLGameObject(name, x, y, framesH, framesV),
	  suit(s),
	  value(val),
	  moveable(can_move),
	  attached(is_attached),
	  begin(can_begin),
	  isUp(is_up),
	  moving(is_moving),
	  onTop(on_top)

{
	if (suit == 'H' || suit == 'D')
		color = 'R';
	else
		color = 'B';

	SetVariableAlarm(0, 1);

	//No collision detection
	GetSprite()->SetPerformCollisionDetection(false);
}

/***************************************************************
Updates the card object
***************************************************************/
void Card::Update(const sf::Time & DeltaTime)
{
	if (begin)
	{
		//If the mouse pointer is intersecting with the card
		if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
		{
			if (moveable && attached)
			{
				//If the mouse is over the top of the card and it is attached to another card
				if ((SFMLMouse::GetInstance()->GetPosition().y >= GetSprite()->Y()
					&& SFMLMouse::GetInstance()->GetPosition().y <= GetSprite()->Y() + 30) ||
					onTop)
				{
					//If the button is just pressed, set holdX, holdY
					if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Left))
					{
						//Move to top of objects
						SetDepth(100);

						//Set hold position
						holdX = SFMLMouse::GetInstance()->GetPosition().x - GetSprite()->X();
						holdY = SFMLMouse::GetInstance()->GetPosition().y - GetSprite()->Y();

						moving = true;
					}

					//The mouse is being held down
					if (SFMLMouse::GetInstance()->IsButtonDown(sf::Mouse::Left) && moving)
					{
						//Freeze all other cards
						Deck::GetDeck()->freezeDeck(this);
						CardStack::GetCardStack()->freezeStacks(this);

						//Set to mouse's position
						GetSprite()->SetX(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x - holdX));
						GetSprite()->SetY(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y - holdY));

						//Move attached cards
						CardStack::GetCardStack()->moveAttached(this);
					}

					//If the button is just released, check if the card can be placed on a stack
					else if (SFMLMouse::GetInstance()->IsButtonReleased(sf::Mouse::Left))
					{
						if (isOverStack())
							CardStack::GetCardStack()->addToStack(this);
						else if (isOverSlots())
							UpperCardSlots::GetUpperCardSlots()->addToSlots(this);
						else
							CardStack::GetCardStack()->returnAttached(this);

						//Reset deck and stacks
						CardStack::GetCardStack()->resetStacks();
						Deck::GetDeck()->resetDeck();

						moving = false;
					}
				}
			}
			//If the card is not attached
			else if (moveable)
			{
				//If the button is just pressed, set holdX, holdY
				if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Left))
				{
					//Move to top of objects
					SetDepth(100);

					//Set hold position
					holdX = SFMLMouse::GetInstance()->GetPosition().x - GetSprite()->X();
					holdY = SFMLMouse::GetInstance()->GetPosition().y - GetSprite()->Y();

					//Set moving
					moving = true;
				}

				//If the mouse button is being held down, set the card's position to the mouse's potision
				if (SFMLMouse::GetInstance()->IsButtonDown(sf::Mouse::Left) && moving)
				{
					//Move to top of objects
					SetDepth(100);

					GetSprite()->SetX(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x - holdX));
					GetSprite()->SetY(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y - holdY));

					//Freeze all other cards
					Deck::GetDeck()->freezeDeck(this);
					CardStack::GetCardStack()->freezeStacks(this);
				}

				//If the button is just released, check if the card can be placed on a stack
				else if (SFMLMouse::GetInstance()->IsButtonReleased(sf::Mouse::Left))
				{
					if (isOverStack())
						CardStack::GetCardStack()->addToStack(this);
					else if (isOverSlots())
						UpperCardSlots::GetUpperCardSlots()->addToSlots(this);
					else
						returnCard();

					//Reset deck and stacks
					CardStack::GetCardStack()->resetStacks();
					Deck::GetDeck()->resetDeck();

					//Stop moving
					moving = false;
				}
			}	
		}
	}
	//Updates the underlying game object
	SFMLGameObject::Update(DeltaTime);
}

/***************************************************************
Returns true if the card is placed over the card stacks and
false if it is not
***************************************************************/
bool Card::isOverStack()
{
	if (SFMLMouse::GetInstance()->GetPosition().y >= 240)
	{
		//Intersects any of the card stacks
		if (SFMLMouse::GetInstance()->GetPosition().x >= 100 && SFMLMouse::GetInstance()->GetPosition().x <= 1212)
			return true;
	}
	return false;
}

/***************************************************************
Returns true if the card is placed over the upper card slots and
false if it is not
***************************************************************/
bool Card::isOverSlots()
{
	if (SFMLMouse::GetInstance()->GetPosition().y >= 20 && SFMLMouse::GetInstance()->GetPosition().y <= 240)
	{
		//Intersects any of the card stacks
		if (SFMLMouse::GetInstance()->GetPosition().x >= 592 && SFMLMouse::GetInstance()->GetPosition().x <= 1212)
			return true;
	}
	return false;
}

/***************************************************************
Handles alarms
***************************************************************/
void Card::OnVariableAlarm(int alarmNumber)
{
	if (alarmNumber == 0)
	{
		begin = true;
	}
}

/***************************************************************
Returns the card to its resting position
***************************************************************/
void Card::returnCard()
{
	GetSprite()->SetX(getPreviousX());
	GetSprite()->SetY(getPreviousY());

	CardStack::GetCardStack()->resetStacks();
	Deck::GetDeck()->resetDeck();
}

/***************************************************************
Sets the card's resting position
***************************************************************/
void Card::setRestingPosition(float x, float y)
{
	previousX = x;
	previousY = y;
}

/***************************************************************
Returns if two cards are equal or not
***************************************************************/
bool Card::operator ==(Card * card2)
{
	if (getFaceValue() == card2->getFaceValue() && getSuit() == card2->getSuit())
		return true;
	else
		return false;
}

/***************************************************************
Returns if two cards are not equal or not
***************************************************************/
bool Card::operator !=(Card * card2)
{
	return !(this == card2);
}