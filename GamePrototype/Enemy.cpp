#include "pch.h"
#include "Enemy.h"
#include "Ball.h"
#include "Humanoid.h"
#include <iostream>

Enemy::Enemy(Ball* ball, std::vector<Humanoid*> humanoids, float difficulty) :
	Humanoid(),
	m_List{ humanoids },
	m_pBall{ ball },
	m_Difficulty{ difficulty }
{
	SetColor(Color4f(0, 1, 0, 1));
}

void Enemy::Update(float elapsedSec)
{
	Vector2f enemyToBall{ m_pBall->GetPosition() - this->GetPosition() };
	const int maxReductionPercentage{ (100 - int(m_Difficulty)) };
	const int rng{ (rand() % maxReductionPercentage) - (maxReductionPercentage / 2) };
	const float reactionOffset{ (ENEMY_REACTION_OFFSET + (ENEMY_REACTION_OFFSET / 100.f) * rng) };
	const float reactionDistance{ ENEMY_REACTION_RANGE + 0 /*reactionOffset*/ };
	
	//std::cout << reactionDistance << std::endl;
	if (enemyToBall.Length() < reactionDistance) {
		const Vector2f randomDirection{ GetPosition() + Vector2f( float(rand()%100) , float(rand()%100) ) };
		//AttackPlayer(randomDirection.ToPoint2f(), m_pBall, m_List);
	}

	Humanoid::Update(elapsedSec);
}
