#ifndef SFMLSPRITE_H
#define SFMLSPRITE_H

class SFMLGameObject;

class SFMLSprite
{
public:
	// Constructor
	SFMLSprite(SFMLGameObject * parent, const std::string & resourceName, float x, float y, int framesHorizontal = 1, int framesVertical = 1);
	// Destructor
	~SFMLSprite();
	// Update
	virtual void Update(const sf::Time & DeltaTime);
	// Draw
	virtual void Draw();

	bool PerformCollisionDetection();
	void SetPerformCollisionDetection( bool value );

	sf::Color Tint();
	void SetTint( const sf::Color value );

	const sf::Texture * Texture();
	void SetTexture( const std::string & resourceKey );

	// Once you rotate things do not think your bounding boxes will work correctly!
	float ImageAngle();
	void SetImageAngle( float value );

	float XScale();
	void SetXScale(float value);

	float YScale();
	void SetYScale(float value);

	float XOffset();
	void SetXOffset(float value);

	float YOffset();
	void SetYOffset(float value);

	bool Visible();
	void SetVisible(bool value);

	int ImageNumber();

	float ImageIndex();
	void SetImageIndex(float value);

	float ImageSpeed();
	void SetImageSpeed(float value);

	int SpriteWidth();
	int SpriteHeight();

	float Direction();
	void SetDirection(float value);

	float Friction();
	void SetFriction(float value);

	float Acceleration();
	void SetAcceleration(float value);

	float AccelerationDirection();
	void SetAccelerationDirection(float value);

	float HSpeed();
	void SetHSpeed(float value);

	float VSpeed();
	void SetVSpeed(float value);

	float Speed();
	void SetSpeed(float value);

	float X();
	void SetX(float value);

	float Y();
	void SetY(float value);

	float XPrevious();
	void SetXPrevious(float value);

	float YPrevious();
	void SetYPrevious(float value);

	float XStart();
	void SetXStart(float value);

	float YStart();
	void SetYStart(float value);

	float DistanceToPoint(float x, float y);

	void MotionAdd(float direction, float speed);

	void MotionSet(float direction, float speed);

	void MoveTowardPoint(float x, float y, float speed);

	void MoveRandom(float hsnap, float ysnap);

	void MoveSnap(float hsnap, float ysnap);

	void MoveWrap(bool hwrap, bool ywrap);

private:
	// Parent game object
	SFMLGameObject * Parent;
	// The sprite object itself
	sf::Sprite * Sprite;
	// Starting position
	sf::Vector2f StartingPosition;
	// Previous position
	sf::Vector2f PreviousPosition;
	// Velocity
	sf::Vector2f VelocityVector;
	// Acceleration
	sf::Vector2f AccelerationVector;
	// Direction
	float DirectionValue;
	// Friction
	float FrictionValue;
	// Acceleration Direction
	float AccelerationDirectionValue;
	// Image index
	float ImageIndexValue;
	// Image speed
	float ImageSpeedValue;
	// Horizontal frames
	int HorizontalImageNumber;
	// Vertical frames
	int VerticalImageNumber;
	// Animation frame value
	int ImageNumberValue;
	// Visible
	bool VisibleValue;
	// Perform collision detection
	bool PerformCollisionDetectionValue;
};

#endif