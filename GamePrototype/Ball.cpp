#include "pch.h"
#include "Ball.h"
#include "Humanoid.h"

Ball::Ball() : Ball(Vector2f{ 0,0 })
{
}

Ball::Ball(const Vector2f& origin) :
	m_Position{ origin },
	m_Speed{ DEFAULT_BALL_SPEED },
	m_Target{ nullptr },
	m_BallClock{ 0 }
{
}

void Ball::Update(float elapsedSec)
{
	if (m_Target != nullptr) {
		GoTo(elapsedSec, m_Target->GetPosition() + Vector2f(m_Target->GetHitbox().width/2,m_Target->GetHitbox().height/2) );
	}
	if (GetSpeed() < BALL_MAX_SPEED) {
		SetSpeed(GetSpeed() + BALL_SPEED_INCREASE * elapsedSec);
	}
	m_BallClock += elapsedSec;
	
}

void Ball::Draw() const
{
	utils::SetColor(Color4f(1, 0, 0, 1));
	const Ellipsef ballAppearance{ m_Position.ToPoint2f(), DEFAULT_BALL_RADIUS ,DEFAULT_BALL_RADIUS };
	utils::FillEllipse(ballAppearance);
}

void Ball::GoTo(float elapsedSec,const Vector2f targetPosition)
{
	const Vector2f targetToBallVector{ (targetPosition - m_Position).Normalized() };
	m_Position += (targetToBallVector * m_Speed) * elapsedSec;
}
