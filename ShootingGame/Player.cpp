#include "Player.h"

#include "Bullet.h"
#include "LightSpot.h"


Player::Player()
{

	x = 0;
	y = 0;
	gunCoolDown = 10;
	gunHeat = 10;
}


Player::~Player()
{
}



void Player::update()
{
	--gunHeat;
	if (gunHeat < 0)
	{
		gunHeat = 0;
	}
}
