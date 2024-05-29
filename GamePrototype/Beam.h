#pragma once
#include "pch.h"
#include "Player.h"
#include "Attack.h"

class Beam : public Attack
{
public:
	explicit Beam(Player* target);
	virtual void Draw() const override;
private:
	Vector2f m_BeamOrigin;
	float m_Width;
};

