#include "Player.h"

#include "Bullet.h"
#include "LightSpot.h"


Player::Player()
{

	x = 0;
	y = 0;
	gunCoolDown = 10 * 2;
	gunHeat = 10;
	walkCoolDown = 3 * 2;
	walkHeat = 0;
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

	--walkHeat;
	if (walkHeat < 0)
	{
		walkHeat = 0;
	}
}
