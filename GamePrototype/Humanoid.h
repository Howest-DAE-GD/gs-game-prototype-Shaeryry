#pragma once
#include "pch.h"
#include "utils.h"

class Ball;
class Weapon;
class Humanoid
{
public:
	explicit Humanoid(const Vector2f& origin,const Rectf& hitbox);
	explicit Humanoid();
	Humanoid(const Humanoid& other) = delete;
	Humanoid& operator=(const Humanoid& other) = delete;
	virtual ~Humanoid();

	virtual void Update(float elapsedSec);
	virtual void Draw() const;

	void TakeDamage(int damage);
	void SetHealth(int health) { m_Health = health; };
	void MoveTo(float elaspedSec, const Vector2f& target);
	void SetPosition(const Vector2f& position) { m_Position = position; };

	void SetColor(const Color4f& newColor) { m_Color = newColor; }
	int GetHealth() const { return m_Health; };
	Vector2f GetPosition() const { return m_Position; };		
	Rectf GetHitbox() const { return m_Hitbox; }; 
protected:
	// Addons
	float m_AttackClock;
	// 
	Color4f m_Color;
	Rectf m_Hitbox;

	Vector2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_CurrentVelocity;

	int m_Health;
	float m_MovementSpeed;
	float m_JumpPower;
	float m_Gravity;
};

