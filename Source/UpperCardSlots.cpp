/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/23/2015
Last Updated On:	5/9/2015
File Name:			UpperCardSlots.cpp
Version:			1.7

----------Description----------
The Upper Card Slots hold the four stacks of cards based on their
matching suits.  If all the cards are placed in the upper card
slots in the proper order, the game is won
***************************************************************/

#include "stdafx.h"
#include "UpperCardSlots.h"
#include "SFMLMouse.h"
#include "Card.h"
#include "Deck.h"
#include "SFMLSprite.h"

#include "MiniPlayGameButton.h"
#include "MiniQuitButton.h"
#include "WinDialog.h"

UpperCardSlots * UpperCardSlots::Instance(nullptr);

/***************************************************************
Constructor for the Card Slots
***************************************************************/
UpperCardSlots::UpperCardSlots()
: SFMLGameObject("UpperSlots", 592, 60)
{
	//No collision detection
	GetSprite()->SetPerformCollisionDetection(false);

	SetDepth(-2);
}

/***************************************************************
Destructor for the Card Slots
***************************************************************/
UpperCardSlots::~UpperCardSlots()
{
	Instance = NULL;
}

/***************************************************************
Updates the Card Stack
***************************************************************/
void UpperCardSlots::Update(const sf::Time & DeltaTime)
{
	//Reset the stacks
	resetSlots();

	//Check for win
	if (heartStack.size() == 13 && spadeStack.size() == 13 &&
		diamondStack.size() == 13 && clubStack.size() == 13)
	{
		MiniPlayGameButton::GetPlayButton()->Display();
		MiniQuitButton::GetQuitButton()->Display();
		WinDialog::GetWinDialog()->Display();
	}

	//Updates the underlying game object
	SFMLGameObject::Update(DeltaTime);
}

/***************************************************************
Returns the instance of the Card Stack
***************************************************************/
UpperCardSlots * UpperCardSlots::GetUpperCardSlots()
{
	if (Instance == nullptr)
	{
		Instance = new UpperCardSlots();
	}

	return Instance;
}

/***************************************************************
Adds the specified card to the card slot if it can be added
***************************************************************/
void UpperCardSlots::addToSlots(Card * card)
{
	int fromStack = CardStack::GetCardStack()->inWhatStack(card);

	//Positioned over spade stack
	if (SFMLMouse::GetInstance()->GetPosition().x >= 592 && SFMLMouse::GetInstance()->GetPosition().x <= 760)
	{
		//Can can be placed on the stack?
		//Is it the ace
		if (card->getSuit() == 'S' && card->getFaceValue() == 1)
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(592);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to spade stack
			spadeStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);
		}
		//Check suit
		else if (card->getSuit() == 'S' && spadeStack.size() > 0  && card->getFaceValue() == (spadeStack.back()->getFaceValue() + 1))
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(592);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to spade stack
			spadeStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);

			//Hide previous card
			spadeStack[spadeStack.size() - 2]->GetSprite()->SetVisible(false);
		}
		else
		{
			if (card->isAttached())
			{
				CardStack::GetCardStack()->returnAttached(card);
			}
			else
				card->returnCard();
		}
	}

	//Positioned over heart stack
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 756 && SFMLMouse::GetInstance()->GetPosition().x <= 884)
	{
		//Can can be placed on the stack?
		//Is it the ace
		if (card->getSuit() == 'H' && card->getFaceValue() == 1)
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(756);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to heart stack
			heartStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);
		}
		//Check suit
		else if (card->getSuit() == 'H' && heartStack.size() > 0 && card->getFaceValue() == (heartStack.back()->getFaceValue() + 1))
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(756);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to heart stack
			heartStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);

			//If the stack has other cards, hide them
			heartStack[heartStack.size() - 2]->GetSprite()->SetVisible(false);
		}
		else
		{
			if (card->isAttached())
			{
				CardStack::GetCardStack()->returnAttached(card);
			}
			else
				card->returnCard();
		}
	}

	//Positioned over club stack
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 920 && SFMLMouse::GetInstance()->GetPosition().x <= 1048)
	{
		//Can can be placed on the stack?
		//Is it the ace
		if (card->getSuit() == 'C' && card->getFaceValue() == 1)
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(920);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to club stack
			clubStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);
		}
		//Check suit
		else if (card->getSuit() == 'C' && clubStack.size() > 0 && card->getFaceValue() == (clubStack.back()->getFaceValue() + 1))
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(920);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to club stack
			clubStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);

			//If the stack has other cards, hide them
			clubStack[clubStack.size() - 2]->GetSprite()->SetVisible(false);
		}
		else
		{
			if (card->isAttached())
			{
				CardStack::GetCardStack()->returnAttached(card);
			}
			else
				card->returnCard();
		}
	}
	//Positioned over diamond stack
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 1084 && SFMLMouse::GetInstance()->GetPosition().x <= 1212)
	{
		//Can can be placed on the stack?
		//Is it the ace
		if (card->getSuit() == 'D' && card->getFaceValue() == 1)
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(1084);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to diamond stack
			diamondStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);
		}
		//Check suit and card value
		else if (card->getSuit() == 'D' && diamondStack.size() > 0 && card->getFaceValue() == (diamondStack.back()->getFaceValue() + 1))
		{
			//Set the position of the sprite
			card->GetSprite()->SetX(1084);
			card->GetSprite()->SetY(60);
			card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

			//-----Add cards to the stack-----

			//Card is from a stack
			if (CardStack::GetCardStack()->isInStack(card))
			{
				CardStack::GetCardStack()->removeFromStack(fromStack);
			}
			//Card is from the deck
			else if (Deck::GetDeck()->IsInDeck(card))
			{
				Deck::GetDeck()->removeFromDeck(card);
			}

			//Add to diamond stack
			diamondStack.push_back(card);

			//Set card state
			card->setAttached(false);
			card->setMoveable(false);
			card->setFaceUp(true);
			card->SetDepth(0);

			//If the stack has other cards, hide them
			diamondStack[diamondStack.size() - 2]->GetSprite()->SetVisible(false);
		}
		else
		{
			if (card->isAttached())
			{
				CardStack::GetCardStack()->returnAttached(card);
			}
			else
				card->returnCard();
		}
	}
	else
	{
		if (card->isAttached())
		{
			CardStack::GetCardStack()->returnAttached(card);
		}
		else
			card->returnCard();
	}

	resetSlots();
}

/***************************************************************
Resets the upper card slots
***************************************************************/
void UpperCardSlots::resetSlots()
{
	if (heartStack.size() > 0)
		heartStack.back()->GetSprite()->SetVisible(true);

	if (clubStack.size() > 0)
		clubStack.back()->GetSprite()->SetVisible(true);

	if (spadeStack.size() > 0)
		spadeStack.back()->GetSprite()->SetVisible(true);

	if (diamondStack.size() > 0)
		diamondStack.back()->GetSprite()->SetVisible(true);

}

/***************************************************************
Displays the Win dialog box
***************************************************************/
void UpperCardSlots::displayWinInfo()
{
	WinDialog::GetWinDialog()->Display();
	MiniPlayGameButton::GetPlayButton()->Display();
	MiniQuitButton::GetQuitButton()->Display();
}

/***************************************************************
Used while testing win scenario
***************************************************************/
void UpperCardSlots::addToSlots(Card * card, int position)
{
	if (position == 1)
	{
		heartStack.push_back(card);
	}
	else if (position == 2)
	{
		diamondStack.push_back(card);
	}
	else if (position == 3)
	{
		spadeStack.push_back(card);
	}
	else if (position == 4)
	{
		clubStack.push_back(card);
	}
}