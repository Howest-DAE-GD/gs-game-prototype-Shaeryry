#include "pch.h"
#include <iostream>
#include "Beam.h"

Beam::Beam(Player* target) :
	Attack(target),
	m_BeamOrigin{ Vector2f(0,0) },
	m_Width{ 100 }
{
	const int rangeOffset{ 125 };
	const float height{ target->GetPosition().y };
	const int offsetHeight{ rand() % rangeOffset };

	m_BeamOrigin.x = 0;
	m_BeamOrigin.y = std::max( GROUND_HEIGHT ,(height + float(offsetHeight)) );

	SetWindup(0.5f);
	SetLength(0.35f);
}

void Beam::Draw() const
{
	const Vector2f beamPosition{
		m_Target->GetPosition().x - (WINDOW_WIDTH / 2),
		m_BeamOrigin.y
	};
	const double sine{ sin(M_PI * (m_AttackClock / 0.05f)) };

	if (WindingUp()) { 

		std::cout << sine << std::endl;
		if (sine > 0) {
			utils::SetColor(Color4f(1, 0, 0, 0.2f));
			utils::FillRect(Rectf(beamPosition.x, beamPosition.y, WINDOW_WIDTH, m_Width));
		}
		//std::cout << "Get ready !" << std::endl;
	}
	else {
		const float widthOffset{ 20 * float(std::round(sine)) };
		const float t{ GetElapsedTimeWithOutWindup() / (m_AttackLength * .5f) };
		const float w{ m_Width };
		utils::SetColor(Color4f(1, 1, 1, 1.f));
		utils::FillRect(Rectf(beamPosition.x, beamPosition.y - (widthOffset / 2), (WINDOW_WIDTH), w + widthOffset));
		//std::cout << "Attack" << std::endl;
	}
}
