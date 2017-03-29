#include "stdafx.h"
#include "SFMLBoundingBox.h"
#include "SFMLContentManager.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLRoom.h"
#include "SFMLSprite.h"

SFMLRoom::SFMLRoom()
	: GameObjects(),
	  CreatedGameObjects(),
	  Font()
{
	SFMLGame::GetInstance()->GetContentManager()->LoadTexture("ascii", "ascii.png");
	Font = new SFMLSprite( nullptr, "ascii", 0, 0, 16, 16 );
	Font->SetPerformCollisionDetection( false );
}

SFMLRoom::~SFMLRoom()
{
	std::vector<SFMLGameObject *>::iterator iter = GameObjects.begin();
	for (; iter != GameObjects.end(); ++iter)
	{
		delete(*iter);
	}
	GameObjects.clear();
	
	delete Font;
}

std::vector<SFMLGameObject *> SFMLRoom::GetGameObjectsAtPoint( float x, float y )
{
	std::vector<SFMLGameObject *> a;

	for (SFMLGameObject * t : GameObjects)
	{
		if (t->Intersects( x, y ))
		{
			a.push_back(t);
		}
	}

	return a;
}


void SFMLRoom::Update(const sf::Time & DeltaTime)
{
	// Add created objects to the vector
	std::copy( CreatedGameObjects.begin(), CreatedGameObjects.end(), back_inserter(GameObjects) );
	CreatedGameObjects.clear();
	
	// Update all the objects
	std::vector<SFMLGameObject *>::iterator iter = GameObjects.begin();
	for (; iter != GameObjects.end(); ++iter)
	{
		(*iter)->Update(DeltaTime);
	}

	// Delete objects that need to be destroyed
	for (std::size_t i = 0; i < GameObjects.size(); ++i)
	{
		if (GameObjects[i]->IsToBeDestroyed() == true)
		{
			delete GameObjects[i];
			GameObjects.erase(GameObjects.begin() + i);
			--i;
		}
	}

	Font->Update( DeltaTime );
}

void SFMLRoom::DrawText( float x, float y, const std::string & phrase, float xscale, float yscale, sf::Color color, const std::string &fontfile )
{
	Font->SetX( x );
	Font->SetY( y );
	Font->SetXScale( xscale );
	Font->SetYScale( yscale );
	Font->SetTint( color );
	Font->SetTexture( fontfile );
	for( int i=0; i<phrase.size(); ++i )
	{
		Font->SetImageIndex( phrase[i] );
		Font->Draw();
		Font->SetX( Font->X() + ( xscale * Font->SpriteWidth() ) );
	}
}

void SFMLRoom::Draw()
{
	std::sort( GameObjects.begin(), 
		       GameObjects.end(), 
		       [] (SFMLGameObject * lhs, SFMLGameObject * rhs) { return lhs->Depth() < rhs->Depth(); } );

	std::vector<SFMLGameObject *>::iterator iter = GameObjects.begin();
	for (; iter != GameObjects.end(); ++iter)
	{
		(*iter)->Draw();
	}
}

void SFMLRoom::InstanceCreate(SFMLGameObject * Object)
{
	CreatedGameObjects.push_back(Object);
}

void SFMLRoom::PerformCollisionDetection(SFMLGameObject * ObjectToTest)
{
	// Get the box
	SFMLBoundingBox * BoxToTest = ObjectToTest->GetBoundingBox();

	std::vector<SFMLGameObject *>::iterator iter = GameObjects.begin();
	for (; iter != GameObjects.end(); ++iter)
	{
		if (ObjectToTest != *iter)
		{
			// Test against all other boxes
			SFMLBoundingBox * BoxToTestAgainst = (*iter)->GetBoundingBox();
			if (BoxToTest->Intersects(BoxToTestAgainst))
			{
				// Call both event handlers
				ObjectToTest->OnCollision(*iter); 
				(*iter)->OnCollision( ObjectToTest );
			}
		}
	}
}