#include "stdafx.h"
#include "SFMLBoundingBox.h"
#include "SFMLSprite.h"

SFMLBoundingBox::SFMLBoundingBox( SFMLSprite * Sprite )
	: AttachedSprite( Sprite )
{
	// Nothing here...
}

bool SFMLBoundingBox::Intersects(float x, float y)
{
	if ((x >= GetRightBounds()) || (x <= GetLeftBounds()) ||
		(y >= GetBottomBounds()) || (y <= GetTopBounds()))
	{
		return false;
	}

	return true;
}

bool SFMLBoundingBox::Intersects(SFMLBoundingBox * OtherBox)
{
	if ((GetRightBounds()  < OtherBox->GetLeftBounds()) ||
		(GetLeftBounds()   > OtherBox->GetRightBounds()) ||
		(GetBottomBounds() < OtherBox->GetTopBounds()) ||
		(GetTopBounds()    > OtherBox->GetBottomBounds()))
	{
		return false;
	}

	return true;
}

float SFMLBoundingBox::GetLeftBounds()
{
	return AttachedSprite->X() - AttachedSprite->XOffset();
}

float SFMLBoundingBox::GetRightBounds()
{
	return GetLeftBounds() + 
				( AttachedSprite->SpriteWidth() * AttachedSprite->XScale() );
}

float SFMLBoundingBox::GetTopBounds()
{
	return AttachedSprite->Y() - AttachedSprite->YOffset();
}

float SFMLBoundingBox::GetBottomBounds()
{
	return GetTopBounds() + 
				( AttachedSprite->SpriteHeight() * AttachedSprite->YScale() );
}