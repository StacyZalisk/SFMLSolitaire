/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/8/2015
Last Updated On:	5/9/2015
File Name:			SolitaireGameRoom.cpp
Version:			1.7

----------Description----------
This file is responsible for creating and running the game room
for a game so Solitaire.  It will create a deck (Deck.h) of 52
cards (Card.h) and use them to play a game of Solitaire.
***************************************************************/

#include "stdafx.h"
#include "SolitaireGameRoom.h"
#include "SFMLContentManager.h"
#include "ReturnToMenuButton.h"
#include "GameBackground.h"
#include "Card.h"
#include "Deck.h"
#include "CardStack.h"
#include "UpperCardSlots.h"
#include "SFMLGame.h"
#include "MiniPlayGameButton.h"
#include "MiniQuitButton.h"
#include "WinDialog.h"

/***************************************************************
Solitiare Game Room Constructor
***************************************************************/
SolitaireGameRoom::SolitaireGameRoom()
{
	//Load non-card graphics into game
	loadOther();

	//Create background
	InstanceCreate(new GameBackground(0, 0));

	//Create Win Dialog
	InstanceCreate(WinDialog::GetWinDialog());

	//Create play button
	InstanceCreate(MiniPlayGameButton::GetPlayButton());

	//Create quit button
	InstanceCreate(MiniQuitButton::GetQuitButton());
	
	//Create return to menu botton
	InstanceCreate(new ReturnToMenuButton(1294, 0));

	//Create upper card slots
	InstanceCreate(UpperCardSlots::GetUpperCardSlots());

	//Create deck
	InstanceCreate(Deck::GetDeck());

	//Create the card stacks
	InstanceCreate(CardStack::GetCardStack());

	//Load all heart cards into the content manager and deck
	loadHearts();
	loadDiamonds();
	loadClubs();
	loadSpades();

	//Shuffle the deck of cards
	Deck::GetDeck()->shuffleDeck();

	//Deal the first hand of cards
	Deck::GetDeck()->firstDeal();
}

/***************************************************************
Loads the provided card into the game by first adding the card
to the game objects through InstanceCreate and then adding
the card to the deck through addCard
***************************************************************/
void SolitaireGameRoom::LoadDeck(Card * card)
{
	//Adds card to the game room
	InstanceCreate(card);

	//Adds card to the deck
	Deck::GetDeck()->addCard(card);
}

/***************************************************************
Loads all the heart cards into the game by loading their
textures into the content manager and then by adding them to 
the game through LoadDeck
***************************************************************/
void SolitaireGameRoom::loadHearts()
{
	//Load graphics for the heart cards
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("AH", "Graphics/AH.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("2H", "Graphics/2H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("3H", "Graphics/3H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("4H", "Graphics/4H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("5H", "Graphics/5H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("6H", "Graphics/6H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("7H", "Graphics/7H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("8H", "Graphics/8H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("9H", "Graphics/9H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("10H", "Graphics/10H.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("JH", "Graphics/JH.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("QH", "Graphics/QH.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("KH", "Graphics/KH.png");

	//Create heart cards and add them to the deck
	LoadDeck(new Card("AH", 100, 60, 2, 1, 'H', 1));
	LoadDeck(new Card("2H", 100, 60, 2, 1, 'H', 2));
	LoadDeck(new Card("3H", 100, 60, 2, 1, 'H', 3));
	LoadDeck(new Card("4H", 100, 60, 2, 1, 'H', 4));
	LoadDeck(new Card("5H", 100, 60, 2, 1, 'H', 5));
	LoadDeck(new Card("6H", 100, 60, 2, 1, 'H', 6));
	LoadDeck(new Card("7H", 100, 60, 2, 1, 'H', 7));
	LoadDeck(new Card("8H", 100, 60, 2, 1, 'H', 8));
	LoadDeck(new Card("9H", 100, 60, 2, 1, 'H', 9));
	LoadDeck(new Card("10H", 100, 60, 2, 1, 'H', 10));
	LoadDeck(new Card("JH", 100, 60, 2, 1, 'H', 11));
	LoadDeck(new Card("QH", 100, 60, 2, 1, 'H', 12));
	LoadDeck(new Card("KH", 100, 60, 2, 1, 'H', 13));
}


/***************************************************************
Loads all the diamond cards into the game by loading their
textures into the content manager and then by adding them to
the game through LoadDeck
***************************************************************/
void SolitaireGameRoom::loadDiamonds()
{
	//Load graphics for the diamond cards
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("AD", "Graphics/AD.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("2D", "Graphics/2D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("3D", "Graphics/3D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("4D", "Graphics/4D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("5D", "Graphics/5D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("6D", "Graphics/6D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("7D", "Graphics/7D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("8D", "Graphics/8D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("9D", "Graphics/9D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("10D", "Graphics/10D.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("JD", "Graphics/JD.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("QD", "Graphics/QD.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("KD", "Graphics/KD.png");

	//Create diamond cards and add them to the deck
	LoadDeck(new Card("AD", 100, 60, 2, 1, 'D', 1));
	LoadDeck(new Card("2D", 100, 60, 2, 1, 'D', 2));
	LoadDeck(new Card("3D", 100, 60, 2, 1, 'D', 3));
	LoadDeck(new Card("4D", 100, 60,  2, 1, 'D', 4));
	LoadDeck(new Card("5D", 100, 60, 2, 1, 'D', 5));
	LoadDeck(new Card("6D", 100, 60, 2, 1, 'D', 6));
	LoadDeck(new Card("7D", 100, 60, 2, 1, 'D', 7));
	LoadDeck(new Card("8D", 100, 60, 2, 1, 'D', 8));
	LoadDeck(new Card("9D", 100, 60, 2, 1, 'D', 9));
	LoadDeck(new Card("10D", 100, 60, 2, 1, 'D', 10));
	LoadDeck(new Card("JD", 100, 60, 2, 1, 'D', 11));
	LoadDeck(new Card("QD", 100, 60, 2, 1, 'D', 12));
	LoadDeck(new Card("KD", 100, 60, 2, 1, 'D', 13));
}

/***************************************************************
Loads all the club cards into the game by loading their
textures into the content manager and then by adding them to
the game through LoadDeck
***************************************************************/
void SolitaireGameRoom::loadClubs()
{
	//Load graphics for the club cards
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("AC", "Graphics/AC.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("2C", "Graphics/2C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("3C", "Graphics/3C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("4C", "Graphics/4C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("5C", "Graphics/5C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("6C", "Graphics/6C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("7C", "Graphics/7C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("8C", "Graphics/8C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("9C", "Graphics/9C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("10C", "Graphics/10C.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("JC", "Graphics/JC.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("QC", "Graphics/QC.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("KC", "Graphics/KC.png");

	//Create club cards and add them to the deck
	LoadDeck(new Card("AC", 100, 60, 2, 1, 'C', 1));
	LoadDeck(new Card("2C", 100, 60, 2, 1, 'C', 2));
	LoadDeck(new Card("3C", 100, 60, 2, 1, 'C', 3));
	LoadDeck(new Card("4C", 100, 60, 2, 1, 'C', 4));
	LoadDeck(new Card("5C", 100, 60, 2, 1, 'C', 5));
	LoadDeck(new Card("6C", 100, 60, 2, 1, 'C', 6));
	LoadDeck(new Card("7C", 100, 60, 2, 1, 'C', 7));
	LoadDeck(new Card("8C", 100, 60, 2, 1, 'C', 8));
	LoadDeck(new Card("9C", 100, 60, 2, 1, 'C', 9));
	LoadDeck(new Card("10C", 100, 60, 2, 1, 'C', 10));
	LoadDeck(new Card("JC", 100, 60, 2, 1, 'C', 11));
	LoadDeck(new Card("QC", 100, 60, 2, 1, 'C', 12));
	LoadDeck(new Card("KC", 100, 60, 2, 1, 'C', 13));
}


/***************************************************************
Loads all the spade cards into the game by loading their
textures into the content manager and then by adding them to
the game through LoadDeck
***************************************************************/
void SolitaireGameRoom::loadSpades()
{
	//Load graphics for the spade cards
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("AS", "Graphics/AS.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("2S", "Graphics/2S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("3S", "Graphics/3S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("4S", "Graphics/4S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("5S", "Graphics/5S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("6S", "Graphics/6S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("7S", "Graphics/7S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("8S", "Graphics/8S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("9S", "Graphics/9S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("10S", "Graphics/10S.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("JS", "Graphics/JS.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("QS", "Graphics/QS.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("KS", "Graphics/KS.png");

	//Create spade cards and add them to the deck
	LoadDeck(new Card("AS", 100, 60, 2, 1, 'S', 1));
	LoadDeck(new Card("2S", 100, 60, 2, 1, 'S', 2));
	LoadDeck(new Card("3S", 100, 60, 2, 1, 'S', 3));
	LoadDeck(new Card("4S", 100, 60, 2, 1, 'S', 4));
	LoadDeck(new Card("5S", 100, 60, 2, 1, 'S', 5));
	LoadDeck(new Card("6S", 100, 60, 2, 1, 'S', 6));
	LoadDeck(new Card("7S", 100, 60, 2, 1, 'S', 7));
	LoadDeck(new Card("8S", 100, 60, 2, 1, 'S', 8));
	LoadDeck(new Card("9S", 100, 60, 2, 1, 'S', 9));
	LoadDeck(new Card("10S", 100, 60, 2, 1, 'S', 10));
	LoadDeck(new Card("JS", 100, 60, 2, 1, 'S', 11));
	LoadDeck(new Card("QS", 100, 60, 2, 1, 'S', 12));
	LoadDeck(new Card("KS", 100, 60, 2, 1, 'S', 13));
}

/***************************************************************
Loads all other graphics into the game
***************************************************************/
void SolitaireGameRoom::loadOther()
{
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("CardBack", "Graphics/CardBack.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("EmptySlot", "Graphics/EmptySlot.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("CardStacks", "Graphics/CardStacks.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("return", "Graphics/returnButton.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("UpperSlots", "Graphics/CardSlots.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("background", "Graphics/gameBackground.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("winBack", "Graphics/winBack.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("miniQuit", "Graphics/quitNew.png");
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("miniNew", "Graphics/playNew.png");
}