#pragma once
#include "Pickup.h"

class Point : public Pickup
{
public:
	explicit Point(Player* player, const Vector2f& position);
	virtual void Update(float elapsedSec);
	void SetScore(int x) { m_Score = x; };
private:
	int m_Score; 
};

