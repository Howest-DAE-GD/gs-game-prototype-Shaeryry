#pragma once
#include "Humanoid.h"

class Ball;
class Enemy final : public Humanoid
{
public:
	explicit Enemy(Ball* ball);
	virtual void Update(float elapsedSec) override;
private:
	Ball* m_pBall;
};

