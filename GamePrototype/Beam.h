#pragma once
#include "pch.h"
#include "Player.h"
#include "Attack.h"

class Beam : public Attack
{
public:
	explicit Beam(Player* target);
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
private:
	Vector2f m_BeamOrigin;
	Vector2f m_BeamPosition;
	float m_Width;
	bool m_CanDamage;
};

