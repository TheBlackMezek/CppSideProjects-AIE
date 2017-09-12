#include "LightSpot.h"



LightSpot::LightSpot(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity(ic, xx, yy, p, m, e, mx, my)
{
	visible = false;
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