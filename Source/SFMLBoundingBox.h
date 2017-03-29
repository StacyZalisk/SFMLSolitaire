#ifndef SFMLBOUNDINGBOX_H
#define SFMLBOUNDINGBOX_H

class SFMLSprite;

class SFMLBoundingBox
{
public:
	SFMLBoundingBox(SFMLSprite * Sprite);

	bool Intersects(float x, float y);
	bool Intersects(SFMLBoundingBox * OtherBox);

	float GetLeftBounds();
	float GetRightBounds();
	float GetTopBounds();
	float GetBottomBounds();

private:
	SFMLSprite * AttachedSprite;
};

#endif