/***************************************************************
Author:				Stacy Zalisk
Creation Date:		4/15/2015
Last Updated On:	5/9/2015
File Name:			CardStack.cpp
Version:			1.7

----------Description----------
The CardStack is used to hold one of the seven stacks of cards
used to move and hold cards in Solitaire.
***************************************************************/

#include "stdafx.h"
#include "CardStack.h"
#include "SFMLMouse.h"
#include "Card.h"
#include "Deck.h"
#include "SFMLSprite.h"

CardStack * CardStack::Instance(nullptr);

/***************************************************************
Constructor for the Card Stack
***************************************************************/
CardStack::CardStack()
	: SFMLGameObject("CardStacks", 100, 240)
{
	//No collision detection
	GetSprite()->SetPerformCollisionDetection(false);
}

/***************************************************************
Destructor for the Card Stack
***************************************************************/
CardStack::~CardStack()
{
	Instance = NULL;
}

/***************************************************************
Updates the Card Stack
***************************************************************/
void CardStack::Update(const sf::Time & DeltaTime)
{
	SetDepth(-1);

	//Updates the underlying game object
	SFMLGameObject::Update(DeltaTime);
}

/***************************************************************
Returns the instance of the Card Stack
***************************************************************/
CardStack * CardStack::GetCardStack()
{
	if (Instance == nullptr)
	{
		Instance = new CardStack();
	}

	return Instance;
}

/***************************************************************
Adds the specified card to the card stack.  Designed to be 
used to determine what stack the card should go on and whether
or not it is able to be placed there
***************************************************************/
void CardStack::addToStack(Card * card)
{
	int fromStack = inWhatStack(card);

	//Positioned over stack1
	if (SFMLMouse::GetInstance()->GetPosition().x >= 100 && SFMLMouse::GetInstance()->GetPosition().x <= 228)
	{
		//Card is not from the same stack
		if (fromStack == 1)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();

			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//stack is empty
		if (stack1.size() <= 0)
		{
			//Card is a king
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(100);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 1);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack1.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack1.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack1.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(100);
				card->GetSprite()->SetY(stack1.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 1);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack1.push_back(card);
				}

				//Attach previous card
				stack1[stack1.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();

			resetStacks();
			return;
		}
	}

	//Positioned over stack2
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 264 && SFMLMouse::GetInstance()->GetPosition().x <= 392)
	{
		//Card is not from the same stack
		if (fromStack == 2)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack2.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(264);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 2);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack2.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack2.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack2.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(264);
				card->GetSprite()->SetY(stack2.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 2);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack2.push_back(card);
				}

				//Attach previous card
				stack2[stack2.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
	}
	//Positioned over stack3
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 428 && SFMLMouse::GetInstance()->GetPosition().x <= 556)
	{
		//Card is not from the same stack
		if (fromStack == 3)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack3.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(428);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 3);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack3.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack3.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack3.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(428);
				card->GetSprite()->SetY(stack3.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 3);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack3.push_back(card);
				}

				//Attach previous card
				stack3[stack3.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
	}
	//Positioned over stack4
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 592 && SFMLMouse::GetInstance()->GetPosition().x <= 720)
	{
		//Card is not from the same stack
		if (fromStack == 4)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
		

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack4.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(592);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				///Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 4);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack4.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack4.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack4.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(592);
				card->GetSprite()->SetY(stack4.back()->GetSprite()->Y() + 30);	
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 4);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack4.push_back(card);
				}

				//Attach previous card
				stack4[stack4.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();

			resetStacks();
			return;
		}
	}
	//Positioned over stack5
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 756 && SFMLMouse::GetInstance()->GetPosition().x <= 884)
	{
		//Card is not from the same stack
		if (fromStack == 5)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack5.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(756);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 5);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack5.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack5.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack5.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(756);
				card->GetSprite()->SetY(stack5.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 5);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack5.push_back(card);
				}

				//Attach previous card
				stack5[stack5.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
	}
	//Positioned over stack6
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 920 && SFMLMouse::GetInstance()->GetPosition().x <= 1048)
	{
		//Card is not from the same stack
		if (fromStack == 6)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack6.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(920);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 6);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack6.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack6.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack6.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(920);
				card->GetSprite()->SetY(stack6.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 6);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack6.push_back(card);
				}

				//Attach previous card
				stack6[stack6.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
	}
	//Positioned over stack7
	else if (SFMLMouse::GetInstance()->GetPosition().x >= 1084 && SFMLMouse::GetInstance()->GetPosition().x <= 1212)
	{
		//Card is not from the same stack
		if (fromStack == 7)
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}

		//Can can be placed on the stack?
		//Card is a king and stack is empty
		if (stack7.size() <= 0)
		{
			if (card->getFaceValue() == 13)
			{
				card->GetSprite()->SetX(1084);
				card->GetSprite()->SetY(240);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 7);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack7.push_back(card);
				}

				card->setFaceUp(true);
				resetStacks();
				card->SetDepth(0);
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		//Check color
		else if (card->getColor() != stack7.back()->getColor())
		{
			//Check face value
			if (card->getFaceValue() == (stack7.back()->getFaceValue() - 1))
			{
				//Set the position of the sprite
				card->GetSprite()->SetX(1084);
				card->GetSprite()->SetY(stack7.back()->GetSprite()->Y() + 30);
				card->setRestingPosition(card->GetSprite()->X(), card->GetSprite()->Y());

				//Add cards to the stack
				if (card->isAttached())
				{
					addAttached(card, 7);
				}
				else
				{
					//Card is from a stack
					if (isInStack(card))
					{
						removeFromStack(fromStack);
					}
					//Card is from the deck
					else if (Deck::GetDeck()->IsInDeck(card))
					{
						Deck::GetDeck()->removeFromDeck(card);
					}

					stack7.push_back(card);
				}

				//Attach previous card
				stack7[stack7.size() - 2]->setAttached(true);
				card->setAttached(true);

				card->setFaceUp(true);
				resetStacks();
				return;
			}
			else
			{
				if (card->isAttached())
				{
					returnAttached(card);
				}
				else
					card->returnCard();

				resetStacks();
				return;
			}
		}
		else
		{
			if (card->isAttached())
			{
				returnAttached(card);
			}
			else
				card->returnCard();
			resetStacks();
			return;
		}
	}
	else
	{
		if (card->isAttached())
		{
			returnAttached(card);
		}
		else
			card->returnCard();
		resetStacks();
		return;
	}
}

/***************************************************************
Adds the specified card to the card stack.  Designed to be used
with the initial deal of the cards
***************************************************************/
void CardStack::addToFirstStack(Card * card, int stackNumber)
{
	if (stackNumber == 1)
	{
		stack1.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(100);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(100, 240);
		card->setMoveable(false);
	}
	else if (stackNumber == 2)
	{
		stack2.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(264);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(264, 240);
		card->setMoveable(false);
	}
	else if (stackNumber == 3)
	{
		stack3.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(428);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(428, 240);
		card->setMoveable(false);
	}
	else if (stackNumber == 4)
	{
		stack4.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(592);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(592, 240);
		card->setMoveable(false);
	}
	else if (stackNumber == 5)
	{
		stack5.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(756);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(756, 240);
		card->setMoveable(false);
	}
	else if (stackNumber == 6)
	{
		stack6.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(920);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(920, 240);
		card->setMoveable(false);
	}
	else
	{
		stack7.push_back(card);
		card->GetSprite()->SetVisible(false);
		card->GetSprite()->SetX(1084);
		card->GetSprite()->SetY(240);
		card->setRestingPosition(1084, 240);
		card->setMoveable(false);
	}
}

/***************************************************************
Adds the specified card to the card stack.
***************************************************************/
void CardStack::addToStack(Card * card, int stackNumber)
{
	if (stackNumber == 1)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(100);
		if (stack1.size() > 0)
			card->GetSprite()->SetY(stack1.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(100, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack1.push_back(card);
	}
	else if (stackNumber == 2)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(264);
		if (stack2.size() > 0)
			card->GetSprite()->SetY(stack2.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(264, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack2.push_back(card);
	}
	else if (stackNumber == 3)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(428);
		if (stack3.size() > 0)
			card->GetSprite()->SetY(stack3.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(428, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack3.push_back(card);
	}
	else if (stackNumber == 4)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(592);
		if (stack4.size() > 0)
			card->GetSprite()->SetY(stack4.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(592, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack4.push_back(card);
	}
	else if (stackNumber == 5)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(756);
		if (stack5.size() > 0)
			card->GetSprite()->SetY(stack5.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(756, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack5.push_back(card);
	}
	else if (stackNumber == 6)
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(920);
		if (stack6.size() > 0)
			card->GetSprite()->SetY(stack6.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(920, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack6.push_back(card);
	}
	else
	{
		card->GetSprite()->SetVisible(true);
		card->GetSprite()->SetImageIndex(1);
		card->GetSprite()->SetX(1084);
		if (stack7.size() > 0)
			card->GetSprite()->SetY(stack7.back()->GetSprite()->Y() + 30);
		else
			card->GetSprite()->SetY(240);
		card->setRestingPosition(1084, card->GetSprite()->Y());
		card->setMoveable(true);
		card->setFaceUp(true);
		stack7.push_back(card);
	}
}

/***************************************************************
Returns true if the card is in the card stacks and false if
it is not
***************************************************************/
bool CardStack::isInStack(Card * card)
{
	//Check if the card is in stack 1
	for (unsigned int i = 0; i < stack1.size(); ++i)
	{
		if (stack1[i] == card)
			return true;
	}
	//Check if the card is in stack 2
	for (unsigned int i = 0; i < stack2.size(); ++i)
	{
		if (stack2[i] == card)
			return true;
	}
	//Check if the card is in stack 3
	for (unsigned int i = 0; i < stack3.size(); ++i)
	{
		if (stack3[i] == card)
			return true;
	}
	//Check if the card is in stack 4
	for (unsigned int i = 0; i < stack4.size(); ++i)
	{
		if (stack4[i] == card)
			return true;
	}
	//Check if the card is in stack 5
	for (unsigned int i = 0; i < stack5.size(); ++i)
	{
		if (stack5[i] == card)
			return true;
	}
	//Check if the card is in stack 6
	for (unsigned int i = 0; i < stack6.size(); ++i)
	{
		if (stack6[i] == card)
			return true;
	}
	//Check if the card is in stack 7
	for (unsigned int i = 0; i < stack7.size(); ++i)
	{
		if (stack7[i] == card)
			return true;
	}
	//Card is not found
	return false;
}

/***************************************************************
Returns the number of the stack the card is found in or 0 if it
is not found
***************************************************************/
int CardStack::inWhatStack(Card * card)
{
	//Check if the card is in stack 1
	for (unsigned int i = 0; i < stack1.size(); ++i)
	{
		if (stack1[i] == card)
			return 1;
	}
	//Check if the card is in stack 2
	for (unsigned int i = 0; i < stack2.size(); ++i)
	{
		if (stack2[i] == card)
			return 2;
	}
	//Check if the card is in stack 3
	for (unsigned int i = 0; i < stack3.size(); ++i)
	{
		if (stack3[i] == card)
			return 3;
	}
	//Check if the card is in stack 4
	for (unsigned int i = 0; i < stack4.size(); ++i)
	{
		if (stack4[i] == card)
			return 4;
	}
	//Check if the card is in stack 5
	for (unsigned int i = 0; i < stack5.size(); ++i)
	{
		if (stack5[i] == card)
			return 5;
	}
	//Check if the card is in stack 6
	for (unsigned int i = 0; i < stack6.size(); ++i)
	{
		if (stack6[i] == card)
			return 6;
	}
	//Check if the card is in stack 7
	for (unsigned int i = 0; i < stack7.size(); ++i)
	{
		if (stack7[i] == card)
			return 7;
	}
	
	return 0;
}

/***************************************************************
Removes the last card from the selected stack
***************************************************************/
void CardStack::removeFromStack(int stackNumber)
{
	if (stackNumber == 1)
		stack1.pop_back();
	else if (stackNumber == 2)
		stack2.pop_back();
	else if (stackNumber == 3)
		stack3.pop_back();
	else if (stackNumber == 4)
		stack4.pop_back();
	else if (stackNumber == 5)
		stack5.pop_back();
	else if (stackNumber == 6)
		stack6.pop_back();
	else if (stackNumber == 7)
		stack7.pop_back();

	resetStacks();
}

/***************************************************************
Resets the stacks to a natural state, with the first card on
all stacks face up and visible
***************************************************************/
void CardStack::resetStacks()
{
	unsigned int i;

	//Reset stack one
	for (i = 0; i < stack1.size(); ++i)
	{
		//Set all cards as not on top
		stack1[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack1.size() - 1)
		{
			stack1[i]->setFaceUp(true);
			stack1[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack1[i]->isFaceUp())
		{
			stack1[i]->setMoveable(true);
			stack1[i]->GetSprite()->SetVisible(true);
			stack1[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack1[i]->isMoving() && stack1[i]->isAttached())
					stack1[i]->SetDepth(23);
				else
					stack1[i]->SetDepth(stack1[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack1[i]->isMoving())
					stack1[i]->SetDepth(0);
			}
				
		}
	}

	//Reset stack two
	for (i = 0; i < stack2.size(); ++i)
	{
		//Set all cards as not on top
		stack2[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack2.size() - 1)
		{
			stack2[i]->setFaceUp(true);
			stack2[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack2[i]->isFaceUp())
		{
			stack2[i]->setMoveable(true);
			stack2[i]->GetSprite()->SetVisible(true);
			stack2[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack2[i]->isMoving() && stack2[i]->isAttached())
					stack2[i]->SetDepth(23);
				else
					stack2[i]->SetDepth(stack2[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack2[i]->isMoving())
					stack2[i]->SetDepth(0);
			}
		}
	}

	//Reset stack three
	for (i = 0; i < stack3.size(); ++i)
	{
		//Set all cards as not on top
		stack3[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack3.size() - 1)
		{
			stack3[i]->setFaceUp(true);
			stack3[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack3[i]->isFaceUp())
		{
			stack3[i]->setMoveable(true);
			stack3[i]->GetSprite()->SetVisible(true);
			stack3[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack3[i]->isMoving() && stack3[i]->isAttached())
					stack3[i]->SetDepth(23);
				else
					stack3[i]->SetDepth(stack3[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack3[i]->isMoving())
					stack3[i]->SetDepth(0);
			}
		}
	}

	//Reset stack four
	for (i = 0; i < stack4.size(); ++i)
	{
		//Set all cards as not on top
		stack4[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack4.size() - 1)
		{
			stack4[i]->setFaceUp(true);
			stack4[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack4[i]->isFaceUp())
		{
			stack4[i]->setMoveable(true);
			stack4[i]->GetSprite()->SetVisible(true);
			stack4[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack4[i]->isMoving() && stack4[i]->isAttached())
					stack4[i]->SetDepth(23);
				else
					stack4[i]->SetDepth(stack4[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack4[i]->isMoving())
					stack4[i]->SetDepth(0);
			}
		}
	}

	//Reset stack five
	for (i = 0; i < stack5.size(); ++i)
	{
		//Set all cards as not on top
		stack5[i]->setOnTop(false);

		//Make sure top card is face up and on top
		if (i == stack5.size() - 1)
		{
			stack5[i]->setFaceUp(true);
			stack5[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack5[i]->isFaceUp())
		{
			stack5[i]->setMoveable(true);
			stack5[i]->GetSprite()->SetVisible(true);
			stack5[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack5[i]->isMoving() && stack5[i]->isAttached())
					stack5[i]->SetDepth(23);
				else
					stack5[i]->SetDepth(stack5[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack5[i]->isMoving())
					stack5[i]->SetDepth(0);
			}
		}
	}

	//Reset stack six
	for (i = 0; i < stack6.size(); ++i)
	{
		//Set all cards as not on top
		stack6[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack6.size() - 1)
		{
			stack6[i]->setFaceUp(true);
			stack6[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack6[i]->isFaceUp())
		{
			stack6[i]->setMoveable(true);
			stack6[i]->GetSprite()->SetVisible(true);
			stack6[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack6[i]->isMoving() && stack6[i]->isAttached())
					stack6[i]->SetDepth(23);
				else
					stack6[i]->SetDepth(stack6[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack6[i]->isMoving())
					stack6[i]->SetDepth(0);
			}
		}
	}

	//Reset stack seven
	for (i = 0; i < stack7.size(); ++i)
	{
		//Set all cards as not on top
		stack7[i]->setOnTop(false);

		//Make sure top card is face up
		if (i == stack7.size() - 1)
		{
			stack7[i]->setFaceUp(true);
			stack7[i]->setOnTop(true);
		}

		//Adjust all face up cards
		if (stack7[i]->isFaceUp())
		{
			stack7[i]->setMoveable(true);
			stack7[i]->GetSprite()->SetVisible(true);
			stack7[i]->GetSprite()->SetImageIndex(1);
			if (i > 0)
			{
				if (stack7[i]->isMoving() && stack7[i]->isAttached())
					stack7[i]->SetDepth(23);
				else
					stack7[i]->SetDepth(stack7[i - 1]->Depth() + 1);
			}
			else
			{
				if (!stack7[i]->isMoving())
					stack7[i]->SetDepth(0);
			}
		}
	}
}

/***************************************************************
Freezes the card stacks
***************************************************************/
void CardStack::freezeStacks(Card * card)
{
	//Freeze stack one
	for (unsigned int i = 0; i < stack1.size(); ++i)
	{
		if (stack1[i] != card)
			stack1[i]->setMoveable(false);
	}

	//Freeze stack two
	for (unsigned int i = 0; i < stack2.size(); ++i)
	{
		if (stack2[i] != card)
			stack2[i]->setMoveable(false);
	}

	//Freeze stack three
	for (unsigned int i = 0; i < stack3.size(); ++i)
	{
		if (stack3[i] != card)
			stack3[i]->setMoveable(false);
	}

	//Freeze stack four
	for (unsigned int i = 0; i < stack4.size(); ++i)
	{
		if (stack4[i] != card)
			stack4[i]->setMoveable(false);
	}

	//Freeze stack five
	for (unsigned int i = 0; i < stack5.size(); ++i)
	{
		if (stack5[i] != card)
			stack5[i]->setMoveable(false);
	}

	//Freeze stack six
	for (unsigned int i = 0; i < stack6.size(); ++i)
	{
		if (stack6[i] != card)
			stack6[i]->setMoveable(false);
	}

	//Freeze stack seven
	for (unsigned int i = 0; i < stack7.size(); ++i)
	{
		if (stack7[i] != card)
			stack7[i]->setMoveable(false);
	}
}

/***************************************************************
Moves all cards attached to each other
***************************************************************/
void CardStack::moveAttached(Card * card)
{
	int stackNum = inWhatStack(card);
	unsigned int i, count;

	//In stack 1
	if (stackNum == 1)
	{
		count = 1; 

		//Increase i until the provided card is hit
		for (i = 0; i < stack1.size() && stack1[i] != card; ++i);

		//Set depth of top card
		stack1[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack1.size())
		{
			//Move the card with the other cards
			stack1[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack1[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack1[i]->SetDepth(stack1[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}
	//In stack 2
	else if (stackNum == 2)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack2.size() && stack2[i] != card; ++i);

		//Set depth of top card
		stack2[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack2.size())
		{
			//Move the card with the other cards
			stack2[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack2[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack2[i]->SetDepth(stack2[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;			
		}
	}
	//In stack 3
	else if (stackNum == 3)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack3.size() && stack3[i] != card; ++i);

		//Set depth of top card
		stack3[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack3.size())
		{
			//Move the card with the other cards
			stack3[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack3[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack3[i]->SetDepth(stack3[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}
	//In stack 4
	else if (stackNum == 4)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack4.size() && stack4[i] != card; ++i);

		//Set depth of top card
		stack4[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack4.size())
		{
			//Move the card with the other cards
			stack4[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack4[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack4[i]->SetDepth(stack4[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}
	//In stack 5
	else if (stackNum == 5)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack5.size() && stack5[i] != card; ++i);

		//Set depth of top card
		stack5[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack5.size())
		{
			//Move the card with the other cards
			stack5[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack5[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack5[i]->SetDepth(stack5[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}
	//In stack 6
	else if (stackNum == 6)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack6.size() && stack6[i] != card; ++i);

		//Set depth of top card
		stack6[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack6.size())
		{
			//Move the card with the other cards
			stack6[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack6[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack6[i]->SetDepth(stack6[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}
	//In stack 7
	else if (stackNum == 7)
	{
		count = 1;

		//Increase i until the provided card is hit
		for (i = 0; i < stack7.size() && stack7[i] != card; ++i);

		//Set depth of top card
		stack7[i]->SetDepth(32);

		//Increase i one more time
		++i;

		while (i < stack7.size())
		{
			//Move the card with the other cards
			stack7[i]->GetSprite()->SetX(card->GetSprite()->X());
			stack7[i]->GetSprite()->SetY(card->GetSprite()->Y() + (count * 30));

			if (count > 1)
				//Set the depth of the card
				stack7[i]->SetDepth(stack7[i - i]->Depth() + 1);

			//Increase i and count
			++i;
			++count;
		}
	}

	resetStacks();
}

/***************************************************************
Returns a stack of attached cards to their resting position
***************************************************************/
void CardStack::returnAttached(Card * card)
{
	int stackNum = inWhatStack(card);
	unsigned int i;

	//In stack 1
	if (stackNum == 1)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack1.size() && stack1[i] != card; ++i);

		while (i < stack1.size())
		{
			stack1[i]->returnCard();
			++i;
		}
	}
	//In stack 2
	else if (stackNum == 2)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack2.size() && stack2[i] != card; ++i);

		while (i < stack2.size())
		{
			stack2[i]->returnCard();
			++i;
		}
	}
	//In stack 3
	else if (stackNum == 3)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack3.size() && stack3[i] != card; ++i);

		while (i < stack3.size())
		{
			stack3[i]->returnCard();
			++i;
		}
	}
	//In stack 4
	else if (stackNum == 4)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack4.size() && stack4[i] != card; ++i);

		while (i < stack4.size())
		{
			stack4[i]->returnCard();
			++i;
		}
	}
	//In stack 5
	else if (stackNum == 5)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack5.size() && stack5[i] != card; ++i);

		while (i < stack5.size())
		{
			stack5[i]->returnCard();
			++i;
		}
	}
	//In stack 6
	else if (stackNum == 6)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack6.size() && stack6[i] != card; ++i);

		while (i < stack6.size())
		{
			stack6[i]->returnCard();
			++i;
		}
	}
	//In stack 7
	else if (stackNum == 7)
	{
		//Increase i until the provided card is hit
		for (i = 0; i < stack7.size() && stack7[i] != card; ++i);

		while (i < stack7.size())
		{
			stack7[i]->returnCard();
			++i;
		}
	}
}

/***************************************************************
Adds a series of attached cards to the stack
***************************************************************/
void CardStack::addAttached(Card * card, int stackNum)
{
	unsigned int fromStack = inWhatStack(card), i;

	Card * temp = card;

	if (fromStack == 1)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack1.size() && stack1[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack1.size())
		{
			addToStack(stack1[i], stackNum);

			stack1[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack1.size() - 1; i > 0 && stack1[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 2)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack2.size() && stack2[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack2.size())
		{
			addToStack(stack2[i], stackNum);

			stack2[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack2.size() - 1; i > 0 && stack2[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 3)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack3.size() && stack3[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack3.size())
		{
			addToStack(stack3[i], stackNum);

			stack3[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack3.size() - 1; i > 0 && stack3[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 4)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack4.size() && stack4[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack4.size())
		{
			addToStack(stack4[i], stackNum);

			stack4[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack4.size() - 1; i > 0 && stack4[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 5)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack5.size() && stack5[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack5.size())
		{
			addToStack(stack5[i], stackNum);

			stack5[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack5.size() - 1; i > 0 && stack5[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 6)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack6.size() && stack6[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack6.size())
		{
			addToStack(stack6[i], stackNum);

			stack6[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack6.size() - 1; i > 0 && stack6[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}
	else if (fromStack == 7)
	{
		//Go through stack until you reach the card
		for (i = 0; i < stack7.size() && stack7[i] != card; ++i);

		//Make sure card on top gets attached
		attachBack(stackNum);

		//Add cards until you reach the end of attached
		while (i < stack7.size())
		{
			addToStack(stack7[i], stackNum);

			stack7[i]->setAttached(true);

			++i;
		}

		//Remove cards
		for (i = stack7.size() - 1; i > 0 && stack7[i] != card; --i)
		{
			removeFromStack(fromStack);
		}

		//Remove last card
		removeFromStack(fromStack);
	}

	resetStacks();
}

/***************************************************************
Sets up the card stacks for the first round, where every top
card is face up and the rest are layered
***************************************************************/
void CardStack::setFirstRound()
{
	unsigned int i, offsetValue;

	//Set stack 1
	//Place first card
	offsetValue = 0;
	stack1[0]->GetSprite()->SetImageIndex(1);
	stack1[0]->GetSprite()->SetVisible(true);
	stack1[0]->setFaceUp(true);
	stack1[0]->SetDepth(static_cast<float>(offsetValue));

	//Set stack 2
	//Place first card
	offsetValue = 0;
	stack2[0]->GetSprite()->SetImageIndex(0);
	stack2[0]->GetSprite()->SetVisible(true);
	stack2[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack2.size(); ++i)
	{
		++offsetValue;
		stack2[i]->GetSprite()->SetY(stack2[i - 1]->GetSprite()->Y() + 5);
		stack2[i]->GetSprite()->SetVisible(true);
		stack2[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 1)
		{
			stack2[i]->GetSprite()->SetImageIndex(1);
			stack2[i]->setFaceUp(true);
		}
		else
			stack2[i]->GetSprite()->SetImageIndex(0);

		stack2[i]->setRestingPosition(stack2[i]->GetSprite()->X(), stack2[i]->GetSprite()->Y());
	}

	//Set stack 3
	//Place first card
	offsetValue = 0;
	stack3[0]->GetSprite()->SetImageIndex(0);
	stack3[0]->GetSprite()->SetVisible(true);
	stack3[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack3.size(); ++i)
	{
		++offsetValue;
		stack3[i]->GetSprite()->SetY(stack3[i - 1]->GetSprite()->Y() + 5);
		stack3[i]->GetSprite()->SetVisible(true);
		stack3[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 2)
		{
			stack3[i]->GetSprite()->SetImageIndex(1);
			stack3[i]->setFaceUp(true);
		}
		else
			stack3[i]->GetSprite()->SetImageIndex(0);

		stack3[i]->setRestingPosition(stack3[i]->GetSprite()->X(), stack3[i]->GetSprite()->Y());
	}

	//Set stack 4
	//Place first card
	offsetValue = 0;
	stack4[0]->GetSprite()->SetImageIndex(0);
	stack4[0]->GetSprite()->SetVisible(true);
	stack4[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack4.size(); ++i)
	{
		++offsetValue;
		stack4[i]->GetSprite()->SetY(stack4[i - 1]->GetSprite()->Y() + 5);
		stack4[i]->GetSprite()->SetVisible(true);
		stack4[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 3)
		{
			stack4[i]->GetSprite()->SetImageIndex(1);
			stack4[i]->setFaceUp(true);
		}
		else
			stack4[i]->GetSprite()->SetImageIndex(0);

		stack4[i]->setRestingPosition(stack4[i]->GetSprite()->X(), stack4[i]->GetSprite()->Y());
	}

	//Set stack 5
	//Place first card
	offsetValue = 0;
	stack5[0]->GetSprite()->SetImageIndex(0);
	stack5[0]->GetSprite()->SetVisible(true);
	stack5[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack5.size(); ++i)
	{
		++offsetValue;
		stack5[i]->GetSprite()->SetY(stack5[i - 1]->GetSprite()->Y() + 5);
		stack5[i]->GetSprite()->SetVisible(true);
		stack5[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 4)
		{
			stack5[i]->GetSprite()->SetImageIndex(1);
			stack5[i]->setFaceUp(true);
		}
		else
			stack5[i]->GetSprite()->SetImageIndex(0);

		stack5[i]->setRestingPosition(stack5[i]->GetSprite()->X(), stack5[i]->GetSprite()->Y());
	}

	//Set stack 6
	//Place first card
	offsetValue = 0;
	stack6[0]->GetSprite()->SetImageIndex(0);
	stack6[0]->GetSprite()->SetVisible(true);
	stack6[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack6.size(); ++i)
	{
		++offsetValue;
		stack6[i]->GetSprite()->SetY(stack6[i - 1]->GetSprite()->Y() + 5);
		stack6[i]->GetSprite()->SetVisible(true);
		stack6[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 5)
		{
			stack6[i]->GetSprite()->SetImageIndex(1);
			stack6[i]->setFaceUp(true);
		}
		else
			stack6[i]->GetSprite()->SetImageIndex(0);

		stack6[i]->setRestingPosition(stack6[i]->GetSprite()->X(), stack6[i]->GetSprite()->Y());
	}

	//Set stack 7
	//Place first card
	offsetValue = 0;
	stack7[0]->GetSprite()->SetImageIndex(0);
	stack7[0]->GetSprite()->SetVisible(true);
	stack7[0]->SetDepth(static_cast<float>(offsetValue));
	for (i = 1; i < stack7.size(); ++i)
	{
		++offsetValue;
		stack7[i]->GetSprite()->SetY(stack7[i - 1]->GetSprite()->Y() + 5);
		stack7[i]->GetSprite()->SetVisible(true);
		stack7[i]->SetDepth(static_cast<float>(offsetValue));
		if (i == 6)
		{
			stack7[i]->GetSprite()->SetImageIndex(1);
			stack7[i]->setFaceUp(true);
		}
		else
			stack7[i]->GetSprite()->SetImageIndex(0);

		stack7[i]->setRestingPosition(stack7[i]->GetSprite()->X(), stack7[i]->GetSprite()->Y());
	}

	//Make the cards moveable
	resetStacks();
}

/***************************************************************
Sets the back card in the vector as attached
***************************************************************/
void CardStack::attachBack(int stackNum)
{
	//Stack 1
	if (stackNum == 1)
	{
		if (stack1.size() > 0 && stack1.back()->isFaceUp())
			stack1.back()->setAttached(true);
	}

	//Stack 2
	if (stackNum == 2)
	{
		if (stack2.size() > 0 && stack2.back()->isFaceUp())
			stack2.back()->setAttached(true);
	}

	//Stack 3
	if (stackNum == 3)
	{
		if (stack3.size() > 0 && stack3.back()->isFaceUp())
			stack3.back()->setAttached(true);
	}

	//Stack 4
	if (stackNum == 4)
	{
		if (stack4.size() > 0 && stack4.back()->isFaceUp())
			stack4.back()->setAttached(true);
	}

	//Stack 5
	if (stackNum == 5)
	{
		if (stack5.size() > 0 && stack5.back()->isFaceUp())
			stack5.back()->setAttached(true);
	}

	//Stack 6
	if (stackNum == 6)
	{
		if (stack6.size() > 0 && stack6.back()->isFaceUp())
			stack6.back()->setAttached(true);
	}

	//Stack 7
	if (stackNum == 7)
	{
		if (stack7.size() > 0 && stack7.back()->isFaceUp())
			stack7.back()->setAttached(true);
	}
}