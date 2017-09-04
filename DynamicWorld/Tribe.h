#pragma once
class Tribe
{
public:
	Tribe();
	~Tribe();

	int x;
	int y;

	void sim(int map[], int sizex, int sizey);
};

