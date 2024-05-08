#pragma once
#include "pch.h"
#include "utils.h"

class Humanoid;
class Weapon
{
public:
	explicit Weapon(Humanoid* humanoid,const float offset,const Rectf& hitbox);
	virtual void Update(float elapsedSec);
	virtual void Draw() const;

	void SetHitbox(const Rectf& rect) { m_Hitbox = rect; };
	void SetOffset(const float newOffset) { m_Offset = newOffset; };
	void SetTarget(const Vector2f& target) { m_Target = target; };

	Vector2f GetTarget() const { return m_Target; };
	Vector2f GetPosition() const { return m_Position; };
	float GetOffset() const { return m_Offset; };
	Rectf GetHitbox() const { return m_Hitbox; };
	Vector2f GetCenter() const;
private:
	// Active variables

	float m_WeaponClock;
	Vector2f m_Target;

	//
	float m_Offset;
	Humanoid* m_pHumanoid;
	Rectf m_Hitbox;
	Vector2f m_Position;
};

