#include "Intersection.h"

Intersection::Intersection(std::list<Road> roads, int state)
{
	this->roads = roads;
	this->state = state;
}

void Intersection::DrawRoads(HDC* hdc, RECT &rc)
{
	int X = rc.right / 2;
	int Y = rc.bottom / 2;



	// Draw intersection
	Rect(hdc, X - 50, Y - 50, X + 50, Y + 50, Colors::ASPHALTGREY);
}

void Intersection::ChangeLightState()
{
	state++;

	if (state == 4)
		state = 0;
}
