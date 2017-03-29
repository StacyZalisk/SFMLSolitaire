#include "stdafx.h"
#include "SFMLContentManager.h"
#include "SFMLGame.h"
#include "SFMLGameObject.h"
#include "SFMLRoom.h"
#include "SFMLSprite.h"

SFMLSprite::SFMLSprite( SFMLGameObject * parent, const std::string & resourceName, float x, float y, int framesHorizontal, int framesVertical )
	: Parent( parent ),
	  Sprite( nullptr ),
	  StartingPosition( x, y ),
	  PreviousPosition( x, y ),
	  VelocityVector( 0, 0 ),
	  AccelerationVector( 0, 0 ),
	  DirectionValue( 0 ),
	  FrictionValue( 0 ),
	  AccelerationDirectionValue( 0 ),
	  ImageIndexValue( 0 ),
	  ImageSpeedValue( 0 ),
	  HorizontalImageNumber( framesHorizontal ),
	  VerticalImageNumber( framesVertical ),
	  ImageNumberValue( framesHorizontal * framesVertical ),
	  VisibleValue( true ),
	  PerformCollisionDetectionValue( true )
{
	sf::Texture * texture = 
		SFMLGame::GetInstance()->GetContentManager()->GetTexture( resourceName );

	Sprite = new sf::Sprite( *texture );
	Sprite->setPosition( x, y );
}

SFMLSprite::~SFMLSprite()
{
	delete Sprite;
}

const sf::Texture * SFMLSprite::Texture()
{
	return Sprite->getTexture();
}

void SFMLSprite::SetTexture( const std::string & resourceKey )
{
	Sprite->setTexture( *(SFMLGame::GetInstance()->GetContentManager()->GetTexture( resourceKey ) ) );
}

void SFMLSprite::Update( const sf::Time & DeltaTime )
{
	// Set where we were before moving
	PreviousPosition = Sprite->getPosition();
	// Apply velocity
	Sprite->move( VelocityVector );
	// Apply collision detection and response
	if( PerformCollisionDetectionValue == true )
	{
		SFMLGame::GetInstance()->GetCurrentRoom()->PerformCollisionDetection(Parent);
	}
	// Apply acceleration
	VelocityVector += AccelerationVector;
	// Apply friction
	SetSpeed( std::max<float>( 0, Speed() - abs( FrictionValue ) ) );
	// Update animation information
	SetImageIndex(ImageIndex() + ImageSpeed());
}

float SFMLSprite::ImageAngle()
{
	return Sprite->getRotation();
}

void SFMLSprite::SetImageAngle( float value )
{
	Sprite->setRotation( value );
}

bool SFMLSprite::PerformCollisionDetection()
{
	return PerformCollisionDetectionValue;
}

void SFMLSprite::SetPerformCollisionDetection( bool value )
{
	PerformCollisionDetectionValue = value;
}

float SFMLSprite::XOffset()
{
	return Sprite->getOrigin().x;
}

void SFMLSprite::SetXOffset(float value)
{
	Sprite->setPosition( Sprite->getPosition().x + value - Sprite->getOrigin().x, 
		                 Sprite->getPosition().y );
	Sprite->setOrigin(value, Sprite->getOrigin().y);
}

float SFMLSprite::YOffset()
{
	return Sprite->getOrigin().y;
}

void SFMLSprite::SetYOffset(float value)
{
	Sprite->setPosition( Sprite->getPosition().x,
		                 Sprite->getPosition().y + value - Sprite->getOrigin().y );
	Sprite->setOrigin(Sprite->getOrigin().x, value);
}

sf::Color SFMLSprite::Tint()
{
	return Sprite->getColor();
}
	
void SFMLSprite::SetTint( const sf::Color value )
{
	Sprite->setColor( value );
}


float SFMLSprite::XScale()
{
	return Sprite->getScale().x;
}

void SFMLSprite::SetXScale(float value)
{
	Sprite->setScale(value, Sprite->getScale().y);
}

float SFMLSprite::YScale()
{
	return Sprite->getScale().y;
}

void SFMLSprite::SetYScale(float value)
{
	Sprite->setScale(Sprite->getScale().x, value);
}

bool SFMLSprite::Visible()
{
	return VisibleValue;
}

void SFMLSprite::SetVisible(bool value)
{
	VisibleValue = value;
}

int SFMLSprite::ImageNumber()
{
	return ImageNumberValue;
}

float SFMLSprite::ImageIndex()
{
	return ImageIndexValue;
}

void SFMLSprite::SetImageIndex( float value )
{
	ImageIndexValue = fmod( value, static_cast<float>( ImageNumber() ) );
	if (ImageIndexValue < 0)
	{
		ImageIndexValue += ImageNumber();
	}
}

float SFMLSprite::ImageSpeed()
{
	return ImageSpeedValue;
}

void SFMLSprite::SetImageSpeed( float value )
{
	ImageSpeedValue = value;
}

void SFMLSprite::Draw()
{
	if( Visible() )
	{
		int HorValue = static_cast<int>(ImageIndex()) % HorizontalImageNumber;
		int VertValue = static_cast<int>( ImageIndex() / HorizontalImageNumber );
		Sprite->setTextureRect(sf::IntRect(HorValue*SpriteWidth(), VertValue*SpriteHeight(), SpriteWidth(), SpriteHeight()));
		SFMLGame::GetInstance()->GetWindow()->draw(*Sprite);
	}
}

float DegreesToRadians(float Degrees)
{
	return Degrees * 3.14159265f / 180.0f;
}

float RadiansToDegrees(float Radians)
{
	return Radians * 180.0f / 3.14159265f;
}

int SFMLSprite::SpriteWidth()
{
	return Sprite->getTexture()->getSize().x / HorizontalImageNumber;
}

int SFMLSprite::SpriteHeight()
{
	return Sprite->getTexture()->getSize().y / VerticalImageNumber;
}

float SFMLSprite::Direction()
{
	return DirectionValue;
}

void SFMLSprite::SetDirection(float value)
{
	// Set Direction
	DirectionValue = value;
	// Set Velocity
	float speed = Speed();
	float direction = DegreesToRadians( value );
	VelocityVector = sf::Vector2f( speed * cos( direction ), -speed * sin( direction ) );
}

float SFMLSprite::Friction()
{
	return FrictionValue;
}

void SFMLSprite::SetFriction(float value)
{
	FrictionValue = value;
}

float SFMLSprite::Acceleration()
{
	return sqrt((AccelerationVector.x * AccelerationVector.x) + (AccelerationVector.y * AccelerationVector.y));
}

void SFMLSprite::SetAcceleration(float value)
{
	float direction = DegreesToRadians(AccelerationDirectionValue);
	AccelerationVector = sf::Vector2f(value * cos(direction), -value * sin(direction));
}

float SFMLSprite::AccelerationDirection()
{
	return AccelerationDirectionValue;
}

void SFMLSprite::SetAccelerationDirection(float value)
{
	AccelerationDirectionValue = value;

	float speed = Acceleration();
	float direction = DegreesToRadians(value);
	AccelerationVector = sf::Vector2f(speed * cos(direction), -speed * sin(direction));
}

float SFMLSprite::HSpeed()
{
	return VelocityVector.x;
}

void SFMLSprite::SetHSpeed(float value)
{
	// Set Velocity
	VelocityVector.x = value;
	// Possibly Set Direction
	if( Speed() != 0 )
	{ 
		DirectionValue = RadiansToDegrees( atan2(-VelocityVector.y, VelocityVector.x) );
	}
}

float SFMLSprite::VSpeed()
{
	return VelocityVector.y;
}

void SFMLSprite::SetVSpeed(float value)
{
	// Set Velocity
	VelocityVector.y = value;
	// Possibly Set Direction
	if( Speed() != 0 )
	{
		DirectionValue = RadiansToDegrees(atan2(-VelocityVector.y, VelocityVector.x));
	}
}

float SFMLSprite::Speed()
{
	return sqrt((VelocityVector.x * VelocityVector.x) + (VelocityVector.y * VelocityVector.y));
}

void SFMLSprite::SetSpeed(float value)
{
	// Set Velocity
	float direction = DegreesToRadians(DirectionValue);
	VelocityVector = sf::Vector2f(value * cos(direction), -value * sin(direction));
}

float SFMLSprite::X()
{
	return Sprite->getPosition().x;
}

void SFMLSprite::SetX(float value)
{
	Sprite->setPosition( value, Sprite->getPosition().y );
}

float SFMLSprite::Y()
{
	return Sprite->getPosition().y;
}

void SFMLSprite::SetY(float value)
{
	Sprite->setPosition( Sprite->getPosition().x, value );
}

float SFMLSprite::XPrevious()
{
	return PreviousPosition.x;
}

void SFMLSprite::SetXPrevious(float value)
{
	PreviousPosition.x = value;
}

float SFMLSprite::YPrevious()
{
	return PreviousPosition.y;
}

void SFMLSprite::SetYPrevious(float value)
{
	PreviousPosition.y = value;
}

float SFMLSprite::XStart()
{
	return StartingPosition.x;
}

void SFMLSprite::SetXStart(float value)
{
	StartingPosition.x = value;
}

float SFMLSprite::YStart()
{
	return StartingPosition.y;
}

void SFMLSprite::SetYStart(float value)
{
	StartingPosition.y = value;
}

float SFMLSprite::DistanceToPoint(float x, float y)
{
	// Distance Formula
	float dx = x - Sprite->getPosition().x;
	float dy = y - Sprite->getPosition().y;
	return sqrt((dx * dx) + (dy * dy));
}

void SFMLSprite::MotionAdd(float direction, float speed)
{
	// Set Velocity
	direction = DegreesToRadians(direction);
	VelocityVector += sf::Vector2f(speed * cos(direction), -speed * sin(direction));
	// Set Direction
	DirectionValue = (Speed() != 0) ? RadiansToDegrees(atan2(-VelocityVector.y, VelocityVector.x)) : RadiansToDegrees(direction);
}

void SFMLSprite::MotionSet(float direction, float speed)
{
	// Set Direction
	DirectionValue = direction;
	// Set Velocity
	direction = DegreesToRadians(direction);
	VelocityVector = sf::Vector2f(speed * cos(direction), -speed * sin(direction));
}

void SFMLSprite::MoveTowardPoint(float x, float y, float speed)
{
	float dx = x - Sprite->getPosition().x;
	float dy = y - Sprite->getPosition().y;
	// Set Direction
	float direction = atan2(-dy, dx);
	DirectionValue = RadiansToDegrees(direction);
	// Set Velocity
	VelocityVector = sf::Vector2f(speed * cos(direction), -speed * sin(direction));
}

void SFMLSprite::MoveRandom(float hsnap, float ysnap)
{
	Sprite->setPosition( static_cast<float>(rand() % SFMLGame::GetWindowWidth()), 
		                 static_cast<float>(rand() % SFMLGame::GetWindowHeight()) );
	MoveSnap(hsnap, ysnap);
}

void SFMLSprite::MoveSnap(float hsnap, float ysnap)
{
	if ((hsnap != 0) && (ysnap != 0))
	{
		int x = static_cast<int>(Sprite->getPosition().x / hsnap);
		int y = static_cast<int>(Sprite->getPosition().y / ysnap);
		Sprite->setPosition(x * hsnap, y * ysnap);
	}
}

void SFMLSprite::MoveWrap(bool hwrap, bool ywrap)
{
	if (hwrap)
	{
		float x = static_cast<float>( static_cast<int>( Sprite->getPosition().x ) % SFMLGame::GetWindowWidth() );
		if (x < 0)
		{
			x += SFMLGame::GetWindowWidth();
		}
		SetX(x);
	}

	if (ywrap)
	{
		float y = static_cast<float>( static_cast<int>(Sprite->getPosition().y) % SFMLGame::GetWindowHeight() );
		if (y < 0)
		{
			y += SFMLGame::GetWindowHeight();
		}
		SetY(y);
	}
}