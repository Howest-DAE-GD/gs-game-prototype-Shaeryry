#include "pch.h"
#include "utils.h"
#include "Humanoid.h"
#include "Weapon.h"
#include "Ball.h"
#include <iostream>

Humanoid::Humanoid(const Vector2f& origin, const Rectf& hitbox)
	:
	m_Color{ Color4f(1.f,1.f,1.f,1.f) },
	m_Position{ origin },
	m_Velocity{ 0 ,0 },
	m_Hitbox{ hitbox },
	m_MovementSpeed{ DEFAULT_HUMANOID_MOVEMENT_SPEED },
	m_JumpPower{ DEFAULT_HUMANOID_JUMP_POWER },
	m_Health{ 1 },
	m_AttackClock{ ATTACK_COOLDOWN },
	m_Gravity{ GRAVITY }
{
}

Humanoid::Humanoid()
	: Humanoid(Vector2f(0,0),Rectf(0,0,25,25))
{
}

Humanoid::~Humanoid()
{
}

void Humanoid::Update(float elapsedSec)
{
	const Vector2f prePosition{ m_Position };


	// Gravity
	m_Velocity.y -= m_Gravity;
	m_Position += (m_Velocity * elapsedSec);  

	// "Collision"
	const float GROUND_LEVEL{ GROUND_HEIGHT };
	if (m_Position.y < GROUND_LEVEL) {
		m_Position.y = GROUND_LEVEL;
		m_Velocity.y = 0;
	}

	// Physics
	m_CurrentVelocity = (m_Position - prePosition);

	// Update hitbox 
	m_Hitbox.left = m_Position.x;
	m_Hitbox.bottom = m_Position.y;
}

void Humanoid::Draw() const
{
	const Rectf positionRect{
		m_Position.x,
		m_Position.y,
		m_Hitbox.width,
		m_Hitbox.height
	};

	utils::SetColor(m_Color);
	utils::FillRect(positionRect);

	/*if (m_pWeapon != nullptr) {
		m_pWeapon->Draw();
	}*/
}

void Humanoid::TakeDamage(int damage)
{
	if (GetHealth() > 0) {
		SetHealth(GetHealth() - damage);
	}
	else {
		SetHealth(0);
	}
}

void Humanoid::MoveTo(float elaspedSec,const Vector2f& target)
{
	const float currentSpeed{ m_MovementSpeed };
	const Vector2f humanoidToTarget{ (target - m_Position) };
	const Vector2f movementDifference{ humanoidToTarget.Normalized() * currentSpeed };
	
	SetPosition(m_Position + (movementDifference * elaspedSec));
}
