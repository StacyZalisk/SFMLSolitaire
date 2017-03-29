/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			SolitaireGameRoom.h
Version:			1.7

----------Description----------
This file is responsible for creating and running the game room
for a game so Solitaire.  It will create a deck (Deck.h) of 52 
cards (Card.h) and use them to play a game of Solitaire.

----------Private Variables----------
Deck deck
The deck of cards used for the current game
***************************************************************/

#ifndef SOLITAIREGAMEROOM_H
#define SOLITAIREGAMEROOM_H

#include "SFMLRoom.h"
#include "Deck.h"

class SolitaireGameRoom : public SFMLRoom
{
public:
	SolitaireGameRoom();

	//Adds the cards to the deck
	void LoadDeck(Card *);

private:
	//To load all the heart cards into the game
	void loadHearts();
	//To load all the diamond cards into the game
	void loadDiamonds();
	//To load all the club cards into the game
	void loadClubs();
	//To load all the spade cards into the game
	void loadSpades();
	//To load all other graphics into the game
	void loadOther();
};

#endif