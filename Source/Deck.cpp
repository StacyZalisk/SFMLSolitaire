/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			Deck.cpp
Version:			1.7

----------Description----------
The Deck class is used to hold a collection of 52 cards (from
Card.h).  The deck will keep track of the cards in the deck,
and remove them from the deck once the cards are placed on
the Solitaire game board.
***************************************************************/

#include "stdafx.h"
#include "Deck.h"
#include "SFMLSprite.h"
#include "SFMLMouse.h"

#include "SFMLKeyboard.h"
#include "UpperCardSlots.h"

#include <vector>

Deck * Deck::Instance(nullptr);

/***************************************************************
Returns the instance of the deck
***************************************************************/
Deck * Deck::GetDeck()
{
	if (Instance == nullptr)
	{
		Instance = new Deck();
	}

	return Instance;
}

/***************************************************************
Deck constructor
***************************************************************/
Deck::Deck()
	: SFMLGameObject("EmptySlot", 100, 60, 2, 1)
{
	//No collision detection
	GetSprite()->SetPerformCollisionDetection(false);

	//Sets up randomization for shuffleDeck()
	std::srand(unsigned(std::time(0)));
}

/***************************************************************
Deck destructor
***************************************************************/
Deck::~Deck()
{
	Instance = NULL;
}

/***************************************************************
Updates the deck object
***************************************************************/
void Deck::Update(const sf::Time & DeltaTime)
{
	//If the w key is pressed, force win DISABLED
	/*if (SFMLKeyboard::GetInstance()->IsKeyPressed(sf::Keyboard::W))
		forceWin();*/

	//If the mouse pointer is intersecting with the deck
	if (Intersects(static_cast<float>(SFMLMouse::GetInstance()->GetPosition().x), 
		static_cast<float>(SFMLMouse::GetInstance()->GetPosition().y)))
	{
		//If the button is just pressed deal the cards
		if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Left) && flipped < size)
		{
			deal();
		}
		//Button is pressed and deck is empty
		else if (SFMLMouse::GetInstance()->IsButtonPressed(sf::Mouse::Left) && flipped == size)
		{
			reDeal();
		}

	}

	if (flipped == size)
	{
		//Show empty deck
		GetSprite()->SetImageIndex(1);
	}

	//If the deck has run out of its top three cards, start showing hidden cards
	if (up == 1 && flipped > 1)
	{
		//Make bottom card show up
		deck[flipped - 2]->GetSprite()->SetVisible(true);
		deck[flipped - 2]->setMoveable(false);
	}

	if (flipped > 1)
		deck[flipped - 1]->setMoveable(true);

	resetDeck();

	//Updates the underlying game object
	SFMLGameObject::Update(DeltaTime);
}

/***************************************************************
Deals three cards, or as many as it can if there are less than
three unflipped cards
***************************************************************/
void Deck::deal()
{
	//If there are filpped cards, hide them
	if (flipped != 0)
	{
		for (int i = flipped; i > flipped - 4 && i - 1 >= 0; --i)
		{
			deck[i - 1]->setMoveable(false);
			deck[i - 1]->GetSprite()->SetX(258);
			deck[i - 1]->setRestingPosition(258, 60);
		}
	}

	//Deal three cards
	for (int c = 1; c <= 3 && flipped < size; ++c)
	{
		//"deal" card
		deck[flipped]->GetSprite()->SetVisible(true);

		//set y position
		deck[flipped]->GetSprite()->SetY(60);

		//Set x position
		if (c == 1)
		{
			deck[flipped]->GetSprite()->SetX(258);
			//Check for first card
			if (flipped == 0)
				SetDepth(0);
			else
			deck[flipped]->SetDepth(deck[flipped - 1]->Depth() + 1);
		}
		else if (c == 2)
		{
			deck[flipped]->GetSprite()->SetX(288);
			deck[flipped]->SetDepth(deck[flipped - 1]->Depth() + 1);
		}
		else if (c == 3)
		{
			deck[flipped]->GetSprite()->SetX(318);
			deck[flipped]->SetDepth(deck[flipped - 1]->Depth() + 1);
		}

		//Set top card as moveable
		deck[flipped]->setMoveable(true);

		//Set other cards as stationary, if applicable
		if (c != 1)
			deck[flipped - 1]->setMoveable(false);

		//Set card's resting position
		deck[flipped]->setRestingPosition(deck[flipped]->GetSprite()->X(), deck[flipped]->GetSprite()->Y());

		//Increase flipped
		++flipped;
	}

	up = 3;

	resetDeck();
}

/***************************************************************
Returns the deck to a completely unflipped state
***************************************************************/
void Deck::reDeal()
{
	//Hide cards
	for (int i = 0; i < size; ++i)
	{
		deck[i]->GetSprite()->SetVisible(false);
		deck[i]->setMoveable(false);
		deck[i]->SetDepth(0);
	}

	//Reset flipped
	flipped = 0;

	//Reset up
	up = 0;

	//Reset deck image
	GetSprite()->SetImageIndex(0);
}

/***************************************************************
Adds a single Card object to the deck
***************************************************************/
void Deck::addCard(Card * newCard)
{
	deck.push_back(newCard);
	newCard->SetDepth(0);
	newCard->GetSprite()->SetImageIndex(1);
	newCard->GetSprite()->SetX(100);
	newCard->GetSprite()->SetY(60);
	newCard->setRestingPosition(newCard->GetSprite()->X(), newCard->GetSprite()->Y());
	newCard->setMoveable(false);
	newCard->GetSprite()->SetVisible(false);
}

/***************************************************************
Shuffles the entire deck of cards
***************************************************************/
void Deck::shuffleDeck()
{
	std::random_shuffle(deck.begin(), deck.end());
}

/***************************************************************
Deals the first hand of cards
***************************************************************/
void Deck::firstDeal()
{
	//Deal cards to stack
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 7 - i; j > 0; --j)
		{
			CardStack::GetCardStack()->addToFirstStack(deck.back(), ((7 - j) + 1));
			deck.pop_back();
		}
	}

	//Make cards left in deck appear
	for (unsigned int i = 0; i < deck.size(); ++i)
	{
		deck[i]->GetSprite()->SetVisible(false);
	}

	//Set size of deck
	size = deck.size();

	//Set number of flipped cards
	flipped = 0;

	CardStack::GetCardStack()->setFirstRound();
}

/***************************************************************
Returns true if the card is in the deck and false if it is not
***************************************************************/
bool Deck::IsInDeck(Card * card)
{
	for (unsigned int i = 0; i < deck.size(); ++i)
	{
		if (deck[i] == card)
			return true;
	}
	
	return false;
}

/***************************************************************
Removes the selected card from the deck
***************************************************************/
void Deck::removeFromDeck(Card * card)
{
	std::vector<Card *>::iterator iter = deck.begin();
	while (*iter != card)
	{
		++iter;
	}
	deck.erase(iter);

	//Decrease size
	--size;

	//Decrease flipped
	--flipped;

	//Decrease up
	if (up > 1 || flipped <= 3)
	{
		--up;
	}

	//Make sure up and flip match if you have less than three cards
	if (flipped <= 3)
		up = flipped;

	//Flip next up card
	if (flipped > 0)
		deck[flipped - 1]->setMoveable(true);
}

/***************************************************************
Freezes the flipped cards on the deck unless the provided card
is the moveable card
***************************************************************/
void Deck::freezeDeck(Card * card)
{
	if (flipped > 0)
	{
		if (deck[flipped - 1] != card)
			deck[flipped - 1]->setMoveable(false);
	}
}

/***************************************************************
Freezes the flipped cards on the deck unless the provided card
is the moveable card
***************************************************************/
void Deck::resetDeck()
{
	if (flipped > 0)
	{
		//Make top card movable, all other stationary
		//Three up cards
		if (up == 3 && size >= 3)
		{
			deck[flipped - 1]->setMoveable(true);
			deck[flipped - 2]->setMoveable(false);
			deck[flipped - 3]->setMoveable(false);
		}
		//Two up cards
		else if (up == 2 && size >= 2)
		{
			deck[flipped - 1]->setMoveable(true);
			deck[flipped - 2]->setMoveable(false);
		}
		//One up card
		else if (up == 1 && size >=1)
		{
			deck[flipped - 1]->setMoveable(true);
		}

		//Reset depth
		for (int i = 0; i < flipped; ++i)
		{
			if (i == 0)
				deck[i]->SetDepth(0);
			else
				deck[i]->SetDepth(deck[i - 1]->Depth() + 1);
		}
	}
}

/***************************************************************
Forces a win scenario for the game.  THIS CAN ONLY BE USED IF
THE INITIAL DEAL OF THE DECK NEVER HAPPENED.  IT WILL NEVER
WORK OTHERWISE
***************************************************************/
void Deck::forceWin()
{
	unsigned int value = 1, i = 0, count = 0;

	//Loop through deck, adding cards to the stack
	while (!deck.empty())
	{
		i = 0;
		if (count == 4)
		{
			count = 0;
			++value;
		}

		while (count < 4 && i < deck.size())
		{
			if (deck[i]->getFaceValue() == value)
			{
				if (deck[i]->getSuit() == 'H')
				{
					deck[i]->GetSprite()->SetX(756);
					deck[i]->GetSprite()->SetY(60);
					deck[i]->GetSprite()->SetVisible(true);

					UpperCardSlots::GetUpperCardSlots()->addToSlots(deck[i], 1);
					removeFromDeck(deck[i]);

					++count;
				}
				else if (deck[i]->getSuit() == 'D')
				{
					deck[i]->GetSprite()->SetX(1084);
					deck[i]->GetSprite()->SetY(60);
					deck[i]->GetSprite()->SetVisible(true);

					UpperCardSlots::GetUpperCardSlots()->addToSlots(deck[i], 2);
					removeFromDeck(deck[i]);

					++count;
				}
				else if (deck[i]->getSuit() == 'S')
				{
					deck[i]->GetSprite()->SetX(592);
					deck[i]->GetSprite()->SetY(60);
					deck[i]->GetSprite()->SetVisible(true);

					UpperCardSlots::GetUpperCardSlots()->addToSlots(deck[i], 3);
					removeFromDeck(deck[i]);

					++count;
				}
				else if (deck[i]->getSuit() == 'C')
				{
					deck[i]->GetSprite()->SetX(920);
					deck[i]->GetSprite()->SetY(60);
					deck[i]->GetSprite()->SetVisible(true);

					UpperCardSlots::GetUpperCardSlots()->addToSlots(deck[i], 4);
					removeFromDeck(deck[i]);

					++count;
				}
			}
			++i;
		}
	}
}