#include "stdafx.h"
#include "SFMLBoundingBox.h"
#include "SFMLGameObject.h"
#include "SFMLMouse.h"
#include "SFMLSprite.h"

#include <vector>

SFMLGameObject::SFMLGameObject(const std::string & resourceName, float x, float y, int framesHorizontal, int framesVertical )
	: Sprite( new SFMLSprite( this, resourceName, x, y, framesHorizontal, framesVertical ) ),
	  BoundingBox( new SFMLBoundingBox( Sprite ) ),
	  ShouldDestroy( false ),
	  DepthValue( 0 )
{
	for (int i = 0; i < 10; ++i)
	{
		FixedAlarms[i] = 0;
		VariableAlarms[i] = 0;
	}
}

SFMLGameObject::~SFMLGameObject()
{
	delete Sprite;
	delete BoundingBox;
}

void SFMLGameObject::DrawText( float x, float y, const std::string & phrase, float xscale, float yscale, sf::Color color, const std::string &fontfile )
{
	SFMLGame::GetInstance()->GetCurrentRoom()->DrawText( x, y, phrase, xscale, yscale, color, fontfile );
}

float SFMLGameObject::Depth()
{
	return DepthValue;
}

void SFMLGameObject::SetDepth(float value)
{
	DepthValue = value;
}

std::vector<SFMLGameObject *> SFMLGameObject::GetGameObjectsAtPoint( float x, float y )
{
	return SFMLGame::GetInstance()->GetCurrentRoom()->GetGameObjectsAtPoint( x, y );
}

void SFMLGameObject::Update(const sf::Time & DeltaTime)
{
	if (ShouldDestroy == false)
	{
		// Handle update
		Sprite->Update(DeltaTime);

		// Handle alarms
		for (int i = 0; i < 10; ++i)
		{
			if (FixedAlarms[i] > 0)
			{
				if (--FixedAlarms[i] <= 0)
				{
					OnFixedAlarm(i);
				}
			}

			if (VariableAlarms[i] > 0)
			{
				VariableAlarms[i] -= DeltaTime.asSeconds();
				if (VariableAlarms[i] <= 0)
				{
					OnVariableAlarm(i);
				}
			}
		}
	}
}

void SFMLGameObject::Destroy()
{
	ShouldDestroy = true;
}

bool SFMLGameObject::IsToBeDestroyed()
{
	return ShouldDestroy;
}

bool SFMLGameObject::Intersects(float x, float y)
{
	// If no sprite attached then no intersection
	// If there is one then test the point out with bounding box
	return (GetSprite() == nullptr) ? false : GetBoundingBox()->Intersects(x, y);
}

float SFMLGameObject::VariableAlarm(int AlarmNumber)
{
	return VariableAlarms[AlarmNumber];
}

void SFMLGameObject::SetVariableAlarm(int AlarmNumber, float AlarmValue)
{
	VariableAlarms[AlarmNumber] = AlarmValue;
}

float SFMLGameObject::FixedAlarm(int AlarmNumber)
{
	return FixedAlarms[AlarmNumber];
}

void SFMLGameObject::SetFixedAlarm(int AlarmNumber, float AlarmValue)
{
	FixedAlarms[AlarmNumber] = AlarmValue;
}

void SFMLGameObject::Draw()
{
	if (ShouldDestroy == false)
	{
		Sprite->Draw();
	}
}

SFMLSprite * SFMLGameObject::GetSprite()
{
	return Sprite;
}

SFMLBoundingBox * SFMLGameObject::GetBoundingBox()
{
	return BoundingBox;
}

void SFMLGameObject::OnCollision(SFMLGameObject * Other)
{
	// Nothing here...
}

void SFMLGameObject::OnFixedAlarm(int AlarmNumber)
{
	// Nothing here...
}

void SFMLGameObject::OnVariableAlarm(int AlarmNumber)
{
	// Nothing here...
}