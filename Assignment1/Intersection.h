#pragma once

#include "Road.h"
#include "TrafficLight.h"
#include "Shapes.h"
#include "Colors.h"
#include "stdafx.h"
#include "Constants.h"

class Intersection
{
public:
	std::list<Road> roads;
	int state;

	Intersection();
	Intersection(std::list<Road> roads, int state);

	void DrawRoads(HDC* hdc, RECT &rc);
	void ChangeLightState();
};

