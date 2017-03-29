/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			Deck.h
Version:			1.7

----------Description----------
The Deck class is used to hold a collection of 52 cards (from 
Card.h).  The deck will keep track of the cards in the deck,
and remove them from the deck once the cards are placed on
the Solitaire game board.

----------Private Variables----------
std::vector<Card *> deck
Holds Card pointers, simulating a deck

static Deck * Instance
Holds the actual instance of the deck

int size
Holds the current size of the deck

int flipped
The number of cards in the deck that have been flipped over

int up
The number of cards from the deck that are face up and visible
***************************************************************/

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "CardStack.h"

#include <vector>
#include <string>

class CardStack;
class SFMLGameObject;

class Deck : public SFMLGameObject
{
public:

	virtual void Update(const sf::Time & DeltaTime);

	//Returns the instance of the card stack
	static Deck * GetDeck();

	//Destructor
	~Deck();

	//Adds a card to the deck
	void addCard(Card *);

	//Shuffles the deck
	void shuffleDeck();

	//Deals the first had
	void firstDeal();

	//Redeals the deck if it has been entirely flipped
	void reDeal();

	//Deals a group of cards
	void deal();

	//Returns whether or not the card is in the deck
	bool IsInDeck(Card * card);

	//Removes the selected card from the deck
	void removeFromDeck(Card * card);

	//Freezes all cards in the deck, except for the provided card
	void freezeDeck(Card * card);

	//Resets the top card of the deck
	void resetDeck();

private:
	//Holds the instance of the deck
	static Deck * Instance;

	//Deck constructor
	Deck();

	//The actual deck of cards
	std::vector<Card *> deck;

	//The amount of total cards in the deck
	int size;

	//The amount of cards flipped over
	int flipped;

	//The number of cards current face up
	int up;

	//Forces a win scenario for testing
	void forceWin();
};

#endif