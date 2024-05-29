#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player() :
	Humanoid(),
	m_HoldingDown{ false },
	m_HoldingJump{ false }
{
	SetHealth(10);
}

void Player::Update(float elapsedSec) 
{
	const bool isFalling{ m_CurrentVelocity.y < 0 };

	if (m_HoldingJump and isFalling) {
		m_Gravity = (GRAVITY / 8);
	} else if ( m_HoldingDown and isFalling ) {
		m_Gravity = (GRAVITY * 3);
	} else {
		m_Gravity = GRAVITY;
	};

	Humanoid::Update(elapsedSec);
}
void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym) {
		case SDLK_UP:
			m_HoldingJump = true;
			this->Jump();
			break;
		case SDLK_DOWN:
			m_HoldingDown = true;
			break;
		default:
			break;
	};
}
void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym) { 
		case SDLK_UP:
			m_HoldingJump = false;
			break;
		case SDLK_DOWN:
			m_HoldingDown = false;
			break;
		default:
			break;
	};
};

void Player::Jump()
{
	if (not InAir()) {
		m_Velocity += Vector2f(0, DEFAULT_HUMANOID_JUMP_POWER);
	}
}

bool Player::InAir()
{
	return (GetPosition().y > GROUND_HEIGHT);
}
