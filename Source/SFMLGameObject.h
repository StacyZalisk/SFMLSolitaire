#ifndef SFMLGAMEOBJECT_H
#define SFMLGAMEOBJECT_H

#include "SFMLGame.h"
#include "SFMLRoom.h"

class SFMLBoundingBox;
class SFMLSprite;

class SFMLGameObject
{
public:
	SFMLGameObject(const std::string & resourceName, float x, float y, int framesHorizontal=1, int framesVertical=1);
	virtual ~SFMLGameObject();

	virtual void Update(const sf::Time & DeltaTime);
	virtual void Draw();

	virtual void OnCollision(SFMLGameObject * Other);
	
	void Destroy();
	bool IsToBeDestroyed();

	// Counts down game frames
	virtual void OnFixedAlarm(int AlarmNumber);
	float FixedAlarm(int AlarmNumber);
	void SetFixedAlarm(int AlarmNumber, float AlarmValue);

	// Counts down seconds
	virtual void OnVariableAlarm(int AlarmNumber);
	float VariableAlarm(int AlarmNumber);
	void SetVariableAlarm(int AlarmNumber, float AlarmValue);

	bool Intersects(float x, float y);

	SFMLSprite * GetSprite();
	SFMLBoundingBox * GetBoundingBox();

	void DrawText( float x, float y, const std::string & phrase, float xscale=1, float yscale=1, sf::Color color=sf::Color::White, const std::string &fontfile="ascii" );

	template<class T>
	std::vector<T *> GetGameObjectsOfType();

	template<class T>
	T * GetFirstGameObjectOfType();

	std::vector<SFMLGameObject *> GetGameObjectsAtPoint( float x, float y );

	float Depth();
	void SetDepth(float value);

private:
	SFMLSprite * Sprite;
	SFMLBoundingBox * BoundingBox;
	bool ShouldDestroy;
	float DepthValue;
	float FixedAlarms[10];
	float VariableAlarms[10];
};

template<class T>
std::vector<T *> SFMLGameObject::GetGameObjectsOfType()
{
	return SFMLGame::GetInstance()->GetCurrentRoom()->GetGameObjectsOfType<T>();
}

template<class T>
T * SFMLGameObject::GetFirstGameObjectOfType()
{
	return SFMLGame::GetInstance()->GetCurrentRoom()->GetFirstGameObjectOfType<T>();
}

#endif