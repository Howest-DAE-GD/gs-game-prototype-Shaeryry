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
private:
	bool Moving_Forward;
	bool Moving_Left;
	bool Moving_Right;
	bool Moving_Down;
};

