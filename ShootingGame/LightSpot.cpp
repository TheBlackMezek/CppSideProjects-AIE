#include "LightSpot.h"



LightSpot::LightSpot(int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity('{', xx, yy, p, m, e, mx, my)
{
	visible = false;
	vel.x = 10 * 2;
}


LightSpot::~LightSpot()
{
}



void LightSpot::update()
{
	--vel.x;
	if (vel.x <= 0)
	{
		alive = false;
	}
}