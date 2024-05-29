#include "pch.h"
#include "Attack.h"

Attack::Attack(Player* target) :
	m_Target{ target },
	m_AttackClock{ 0 },
	m_AttackLength{ 1 },
	m_AttackWindup{ 0.5f }
{
}

Attack::~Attack()
{
} 

void Attack::Update(float elapsedSec)
{
	m_AttackClock += elapsedSec;
}
