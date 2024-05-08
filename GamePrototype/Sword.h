#pragma once
#include "pch.h"
#include "utils.h"
#include "Weapon.h"

class Humanoid;
class Sword final : public Weapon
{
public:
	explicit Sword(Humanoid* humanoid);
	virtual void Draw() const override;
private:
	const Vector2f m_SwordOffset{ 5,0 };
	const Rectf m_SwordHitbox{ 0,0,100,200 };
};

