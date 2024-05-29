#pragma once
#include "Humanoid.h"

class Ball;
class Enemy final : public Humanoid
{
public:
	explicit Enemy(Ball* ball,std::vector<Humanoid*> humanoids,float difficulty);
	virtual void Update(float elapsedSec) override;
private:
	float m_Difficulty;
	Ball* m_pBall;
	std::vector<Humanoid*> m_List;
};

