#include "pch.h"
#include "utils.h"
#include "Humanoid.h"
#include "Weapon.h"
#include "Ball.h"
#include <iostream>

Humanoid::Humanoid(const Vector2f& origin, const Rectf& hitbox)
	:
	m_pWeapon{ nullptr },
	m_Color{ Color4f(1.f,1.f,1.f,1.f) },
	m_Position{ origin },
	m_Hitbox{ hitbox },
	m_MovementSpeed{ DEFAULT_HUMANOID_MOVEMENT_SPEED },
	m_Acceleration{ DEFAULT_HUMANOID_ACCELERATION },
	m_Deceleration{ DEFAULT_HUMANOID_DECELERATION },
	m_JumpPower{ DEFAULT_HUMANOID_JUMP_POWER },
	m_CurrentAcceleration{ 0 },
	m_Health{ 1 },
	m_AttackClock{ ATTACK_COOLDOWN }
{
}

Humanoid::Humanoid()
	: Humanoid(Vector2f(0,0),Rectf(0,0,25,25))
{
}

Humanoid::~Humanoid()
{
	GiveWeapon(nullptr);
}

void Humanoid::Update(float elapsedSec)
{
	const Vector2f prePosition{ m_Position };
	// Update others
	/*if (m_pWeapon!=nullptr) {
		m_pWeapon->Update(elapsedSec);
	}*/
	// Physics
	AddAcceleration(-m_Deceleration*elapsedSec); // Deceleration !!
	m_CurrentVelocity = (m_Position - prePosition);

	//// Gravity
	//m_Position.y -= (9.81f * elapsedSec);
	//// "Collision"
	//const float GROUND_LEVEL{ 50 };
	//if (m_Position.y < GROUND_LEVEL) {
	//	m_Position.y = GROUND_LEVEL;
	//}
	m_AttackClock += elapsedSec;
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

void Humanoid::AttackPlayer(const Point2f& mousePosition, Ball* ball, std::vector<Humanoid*> listTargets)
{
	// Get closest target to "mouse position" and set the ball's target to them !
	const Vector2f mouseVector{ Vector2f(mousePosition.x,mousePosition.y) };
	Humanoid* closestTarget{nullptr};
	float closestDistance{ 0 };

	for (size_t humanoidIndex{0}; humanoidIndex < listTargets.size(); humanoidIndex++) {
		Humanoid* humanoidAtIndex{ listTargets[humanoidIndex] };
		if (humanoidAtIndex != this) {
			const Vector2f humanoidToMouse{ humanoidAtIndex->GetPosition() - mouseVector };

			if (humanoidToMouse.Length() <= closestDistance or (closestTarget == nullptr)) {
				closestTarget = humanoidAtIndex;
				closestDistance = humanoidToMouse.Length();
			}
		}
	}

	// Check if you can actually parry it !

	if (closestTarget != nullptr) {
		const bool canParry{ m_AttackClock > ATTACK_COOLDOWN };
		if (canParry) {
			std::cout << "Attacked !" << std::endl;
			const Vector2f ballToPosition{ (ball->GetPosition() - this->GetPosition())};
			// Check if hit (if it's in distance)
			if (ballToPosition.Length() <= 50.f) {
				std::cout << "Hit !" << std::endl;
				ball->SetTarget(closestTarget);
			}
			m_AttackClock = 0;
			// Make it so you cannot parry anymore
		}
	}
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

void Humanoid::AddAcceleration(float accel)
{
	m_CurrentAcceleration += accel;
	if (m_CurrentAcceleration < 0) {
		m_CurrentAcceleration = 0;
	}
	else if (m_CurrentAcceleration >= 100) {
		m_CurrentAcceleration = 100;
	}
}

void Humanoid::MoveTo(float elaspedSec,const Vector2f& target)
{
	AddAcceleration(m_Acceleration*elaspedSec);

	const float currentSpeed{ m_MovementSpeed * (m_CurrentAcceleration / 100) };
	const Vector2f humanoidToTarget{ (target - m_Position) };
	const Vector2f movementDifference{ humanoidToTarget.Normalized() * currentSpeed };
	
	SetPosition(m_Position + (movementDifference * elaspedSec));
}

void Humanoid::GiveWeapon(Weapon* m_Weapon)
{
	if (m_pWeapon != nullptr) {
		delete m_pWeapon;
		m_pWeapon = nullptr;
	};

	if (m_Weapon!=nullptr) {
		m_pWeapon = m_Weapon;
	}
}
