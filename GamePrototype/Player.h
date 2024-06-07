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
	void AddScore(int x) { m_Score += x; };

	bool InAir(); 
	int GetScore() const { return m_Score; };
private:
	int m_Score;
	int m_JumpCount;
	bool m_HoldingJump;
	bool m_HoldingDown;
};

