#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player()
	: 
	Humanoid(),
	Moving_Forward{ false },
	Moving_Left{ false },
	Moving_Down{ false },
	Moving_Right{false}
{
	SetHealth(10);
}

void Player::Update(float elapsedSec)
{
	Vector2f direction{0,0};
	const bool IsMoving{Moving_Forward or Moving_Left or Moving_Right or Moving_Down};

	if (Moving_Left) {
		direction.x -= 1;
	} else if (Moving_Right) {
		direction.x += 1;
	}

	if (Moving_Forward) {
		direction.y = 1;
	} else if (Moving_Down) {
		direction.y = -1;
	}

	if (IsMoving) {
		Humanoid::MoveTo(elapsedSec, GetPosition() + direction);
	}

	Humanoid::Update(elapsedSec);
}


void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym) {
		case FORWARD_KEY:
			Moving_Forward = true;
			break;
		case LEFT_KEY:
			Moving_Left = true;
			break;
		case RIGHT_KEY:
			Moving_Right = true;
			break;
		case DOWN_KEY:
			Moving_Down = true;
			break;
		default:
			break;
	}
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym) {
	case FORWARD_KEY:
		Moving_Forward = false;
		break;
	case LEFT_KEY:
		Moving_Left = false;
		break;
	case RIGHT_KEY:
		Moving_Right = false;
		break;
	case DOWN_KEY:
		Moving_Down = false;
		break;
	default:
		break;
	}
}
