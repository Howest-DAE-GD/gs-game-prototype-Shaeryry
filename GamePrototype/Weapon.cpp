#include "pch.h"
#include "Humanoid.h"
#include "Weapon.h"

Weapon::Weapon(Humanoid* humanoid, const float offset, const Rectf& hitbox) :
	m_pHumanoid{ humanoid },
	m_Position{ 0,0 },
	m_Offset{offset},
	m_Hitbox{hitbox},
	m_WeaponClock{0}
{
}

void Weapon::Update(float elapsedSec)
{
	const Vector2f centerPosition{ GetCenter() };
	const Vector2f centerToTarget{ (m_Target - centerPosition).Normalized() };
	m_Position = centerPosition + (centerToTarget * m_Offset);
	m_WeaponClock += elapsedSec;
}

void Weapon::Draw() const
{
	const Vector2f centerToTarget{ (m_Target - GetCenter() ).Normalized() };
	const float Angle{ float(acos(Vector2f(0,0).DotProduct(centerToTarget)/ Vector2f(0,0).Norm()* centerToTarget.Norm())) };

	glRotatef(Angle,0,0,0);
}

Vector2f Weapon::GetCenter() const
{
	return m_pHumanoid->GetPosition() + Vector2f(m_pHumanoid->GetHitbox().width, m_pHumanoid->GetHitbox().height) / 2;
}
