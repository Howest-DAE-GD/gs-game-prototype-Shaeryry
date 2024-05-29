#pragma once
#include "Player.h"

class Attack
{
public:
	explicit Attack(Player* target);
	virtual ~Attack();
	virtual void Update(float elapsedSec);
	virtual void Draw() const = 0;

	void SetWindup(float x) { m_AttackWindup = x; };
	void SetLength(float x) { m_AttackLength = x; };

	float GetElapsedTime() const { return m_AttackClock; };
	float GetElapsedTimeWithOutWindup() const { return (m_AttackClock - m_AttackWindup); }
	bool HasEnded() const { return GetElapsedTime() >= (m_AttackLength + m_AttackWindup); };
	bool WindingUp() const { return GetElapsedTime() < m_AttackWindup; };
protected:
	Player* m_Target;
	float m_AttackClock;
	float m_AttackLength;
	float m_AttackWindup;
};

