#include "pch.h"
#include "Point.h"
#include "Player.h"
#include <iostream>

Point::Point(Player* player, const Vector2f& position) :
	Pickup(player, position),
	m_Score{ 100 }
{
	SetColor(Color4f(0, 1, 0, 1));
}

void Point::Update(float elapsedSec)
{
	if (HasPickedUp()) {
		m_Player->AddScore(m_Score);
		m_Active = false;
		std::cout << m_Player->GetScore() << std::endl;
	}
	Pickup::Update(elapsedSec);
}
