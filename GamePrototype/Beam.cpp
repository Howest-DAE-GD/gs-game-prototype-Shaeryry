#include "pch.h"
#include <iostream>
#include "Beam.h"

Beam::Beam(Player* target) :
	Attack(target),
	m_BeamOrigin{ Vector2f(0,0) },
	m_BeamPosition{ Vector2f{0,0} },
	m_Width{ 100 },
	m_CanDamage{ true }
{
	const int rangeOffset{ 125 };
	const float height{ target->GetPosition().y };
	const int offsetHeight{ rand() % rangeOffset };

	m_BeamOrigin.x = 0;
	m_BeamOrigin.y = std::max( GROUND_HEIGHT ,std::min( (height + float(offsetHeight) ) , WINDOW_HEIGHT - UI_HEIGHT) );

	SetWindup(1.f);
	SetLength(0.35f);
}

void Beam::Update(float elapsedSec)
{

	m_BeamPosition = Vector2f{
		m_Target->GetPosition().x - (WINDOW_WIDTH / 2),
		m_BeamOrigin.y - UI_HEIGHT
	};

	const Rectf beamRect{
		m_BeamPosition.x,m_BeamPosition.y,WINDOW_WIDTH,m_Width
	};

	const bool hasHit{
		utils::IsOverlapping(m_Target->GetHitbox(),beamRect)
	};

	if (hasHit and not WindingUp() and m_CanDamage) {
		//std::cout << "hit" << std::endl;
		m_CanDamage = false;
		m_Target->TakeDamage(1);
	}


	Attack::Update(elapsedSec);
}

void Beam::Draw() const
{
	const Vector2f beamPosition{ m_BeamPosition };
	const double sine{ sin(M_PI * (m_AttackClock / 0.05f)) };

	if (WindingUp()) { 
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
		const float wFinal{ w + widthOffset };

		utils::SetColor(Color4f(1, 1, 1, 1.f));
		utils::FillRect(Rectf(beamPosition.x, beamPosition.y - (widthOffset / 2), (WINDOW_WIDTH), wFinal));
		//std::cout << "Attack" << std::endl;
	}
}
