#pragma once
#include "pch.h"
#include "Humanoid.h"
#include "Attack.h"

class Player;
class Boss : public Humanoid
{
public:
	explicit Boss(Player* player);
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	void LaunchAttack(Attack* attack);
private:
	float m_BossClock;
	float m_AttackClock;
	Player* m_PlayerTarget;
	std::vector <Attack*> m_Attacks;
};

