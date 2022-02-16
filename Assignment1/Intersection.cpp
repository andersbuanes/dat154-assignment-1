#include "Intersection.h"

Intersection::Intersection() {}

Intersection::Intersection(std::list<Road> roads, int state)
{
	this->roads = roads;
	this->state = state;
}

void Intersection::DrawRoads(HDC* hdc, RECT &rc)
{
	int X = rc.right / 2;
	int Y = rc.bottom / 2;

	// Draw roads
	Rect(hdc, 10, Y - ROAD_WIDTH, rc.right - 10, Y + ROAD_WIDTH, Colors::ASPHALTGREY);
	Rect(hdc, X - ROAD_WIDTH, 10, X + ROAD_WIDTH, rc.bottom - 10, Colors::ASPHALTGREY);

	// Draw lane dividers
	Line(hdc, 10, Y, rc.right - 10, Y, Colors::DIVIDERYELLOW);
	Line(hdc, X, 10, X, rc.bottom - 10, Colors::DIVIDERYELLOW);

	DashedLine(hdc, 10, Y - (ROAD_WIDTH / 2), rc.right - 10, Y - (ROAD_WIDTH / 2), Colors::WHITE);
	DashedLine(hdc, 10, Y + (ROAD_WIDTH / 2), rc.right - 10, Y + (ROAD_WIDTH / 2), Colors::WHITE);
	DashedLine(hdc, X - (ROAD_WIDTH / 2), 10, X - (ROAD_WIDTH / 2), rc.bottom - 10, Colors::WHITE);
	DashedLine(hdc, X + (ROAD_WIDTH / 2), 10, X + (ROAD_WIDTH / 2), rc.bottom - 10, Colors::WHITE);

	// Draw intersection
	Rect(hdc, X - ROAD_WIDTH, Y - ROAD_WIDTH, X + ROAD_WIDTH, Y + ROAD_WIDTH, Colors::INTERSECTIONGREY);
}

void Intersection::ChangeLightState()
{
	state++;

	if (state == 4)
		state = 0;

	for (auto road : roads)
	{
		road.trafficLight.state = state;
	}
}
