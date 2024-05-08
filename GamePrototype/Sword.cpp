#include "pch.h"
#include <iostream>
#include "Weapon.h"
#include "Sword.h"

Sword::Sword(Humanoid* humanoid) :
	Weapon(humanoid, 40, Rectf{  0,0,10,80 })
{
}

void Sword::Draw() const
{
	// Rotation math
	glPushMatrix();
	Weapon::Draw();

	utils::SetColor(Color4f( 209.f/255.f, 84.f/255.f, 163.f/255.f,1.f));
	utils::FillRect( 
		Rectf(
			GetPosition().x,
			GetPosition().y,
			GetHitbox().width,
			GetHitbox().height
		)
	);
	glPopMatrix();
}
