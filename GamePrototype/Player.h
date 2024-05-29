#pragma once
#include "Humanoid.h"

class Ball;
class Player final : public Humanoid
{
public:
	explicit Player();
	virtual void Update(float elapsedSec) override;

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	void Jump();
	void Crouch();

	bool InAir(); 
private:
	bool m_HoldingJump;
	bool m_HoldingDown;
};

