#include "pch.h"
#include <iostream>
#include "Player.h"
#include "Pickup.h"

Pickup::Pickup(Player* player, const Vector2f& position) :
	m_Player{ player },
	m_Active{ true },
	m_Position{ position },
	m_Size{ PICK_UP_DEFAULT_SIZE },
	m_Color{ Color4f(1,1,1,1) },
	m_Clock{ 0 }
{
}

Pickup::Pickup(Player* player)
	: Pickup(player,Vector2f(0,0))
{
}

void Pickup::Draw() const
{
	if (m_Active) {
		const float floatTime{ 2 };
		const float floatiness{ 15.f * float(sin(2 * M_PI* (m_Clock / floatTime) )) };
		utils::SetColor(m_Color);
		utils::FillRect(m_Position.x, m_Position.y + floatiness, m_Size, m_Size);
	}
}

void Pickup::Update(float elapsedSec)
{
	m_Clock += elapsedSec;
}

bool Pickup::HasPickedUp() const
{
	if (m_Active) {
		const Rectf pickupHitbox{
			m_Position.x,
			m_Position.y,
			m_Size,
			m_Size
		};

		const bool pickedUp{ utils::IsOverlapping(pickupHitbox,m_Player->GetHitbox()) };
		return pickedUp;
	}
}
