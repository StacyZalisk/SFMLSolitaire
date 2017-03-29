#include "stdafx.h"
#include "GameBackground.h"
#include "SFMLGameObject.h"

GameBackground::GameBackground(float x, float y)
: SFMLGameObject("background", 0, 0)
{
	SetDepth(-10);
	// Nothing here...
}