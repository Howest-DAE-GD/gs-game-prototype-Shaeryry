#include "pch.h"
#include "Boss.h"
#include "Humanoid.h"
#include "Player.h"

// Attacks

#include "Beam.h"

Boss::Boss(Player* player) :
	Humanoid(),
	m_CanAttack{ false },
	m_BossClock{ 0 },
	m_AttackClock{ 0 },
	m_PlayerTarget{ player }
{
	Reset();
}

Boss::~Boss()
{
	for (size_t attackIndex{}; attackIndex < m_Attacks.size(); attackIndex++) {
		delete m_Attacks[attackIndex];
	};
}

void Boss::Update(float elapsedSec)
{
	for (size_t attackIndex{}; attackIndex < m_Attacks.size(); attackIndex++) {
		m_Attacks[attackIndex]->Update(elapsedSec);
	};
		
	for (size_t attackIndex{}; attackIndex < m_Attacks.size(); attackIndex++) {
		if (m_Attacks[attackIndex] != nullptr) {
			if (m_Attacks[attackIndex]->HasEnded()) {
				delete m_Attacks[attackIndex];
				m_Attacks.erase(m_Attacks.begin() + attackIndex);
				attackIndex--;
			}
		}
	};

	if (m_PlayerTarget->GetHealth() > 0) {
		if (m_AttackClock >= 2) {
			LaunchAttack(new Beam(m_PlayerTarget));
			m_AttackClock = 0;
		}
	};

	m_BossClock += elapsedSec;
	m_AttackClock += elapsedSec;
}

void Boss::Draw() const
{
	const float cycleTime{ 1 };
	const float range{ 60 };  
	glPushMatrix();
	glTranslatef(
		range * float(cos( 1* M_PI* (m_BossClock / cycleTime) )),
		range * float(sin( 2* M_PI * (m_BossClock / cycleTime))),
		0
	);

	Humanoid::Draw();
	glPopMatrix();

	for (size_t attackIndex{}; attackIndex < m_Attacks.size(); attackIndex++) {
		m_Attacks[attackIndex]->Draw();
	};
}

void Boss::LaunchAttack(Attack* attack)
{
	if (m_CanAttack) {
		if (attack != nullptr) {
			m_Attacks.emplace_back(attack);
		}
	}
}

void Boss::Reset()
{
	//m_BossClock = 0;
	m_AttackClock = 0;
	SetActive(false);
}
 