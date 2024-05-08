#include "pch.h"
#include "Enemy.h"
#include "Humanoid.h"

Enemy::Enemy(Ball* ball) :
	Humanoid(),
	m_pBall{ball}
{
	SetColor(Color4f(0, 1, 0, 1));
}

void Enemy::Update(float elapsedSec)
{
	Humanoid::Update(elapsedSec);
}
