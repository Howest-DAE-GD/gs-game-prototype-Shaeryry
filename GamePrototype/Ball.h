#pragma once
#include "pch.h"
#include "utils.h"

class Humanoid;
class Ball final
{
public:
	explicit Ball();
	explicit Ball(const Vector2f& origin);
	void Update(float elapsedSec);
	void Draw() const;
	void GoTo(float elapsedSec,const Vector2f targetPosition);
	void SetSpeed(const float newSpeed) { m_Speed = newSpeed; };
	float GetSpeed() const { return m_Speed; };
	void SetTarget(Humanoid* newTarget) { m_Target = newTarget; };
	Humanoid* GetTarget() const { return m_Target; };
	Vector2f GetPosition() const { return m_Position; };
private:	
	Vector2f m_Position;
	Humanoid* m_Target;
	float m_Speed;
	float m_BallClock;
};

