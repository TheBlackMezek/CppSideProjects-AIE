#pragma once


class Entity
{
private:
	int posx;
	int posy;
	int health;
public:
	int getPosx();
	int getPosy();
	int getHealth();

	void setPosx(int x);
	void setPosy(int y);
	void setHealth(int h);
};