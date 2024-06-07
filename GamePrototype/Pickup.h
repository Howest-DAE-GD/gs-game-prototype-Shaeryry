#pragma once
#include "pch.h"
#include "utils.h"

class Player;
class Pickup	
{
public:
	explicit Pickup(Player* player,const Vector2f& position);
	explicit Pickup(Player* player);
	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	void SetColor(const Color4f& color) { m_Color = color; };
	void SetScale(float x) { m_Size = x; };
	bool HasPickedUp() const;
protected:
	bool m_Active;
	Player* m_Player;
	Vector2f m_Position;
	Color4f m_Color;
	float m_Size;
	float m_Clock;
};

