#pragma once

#include "stdafx.h"
#include "Car.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"
#include "TrafficLight.h"
#include "Direction.h"

class Road
{
public:
	std::list<Car> cars;
	TrafficLight trafficLight;
	int p;
	
	Road();
	Road(std::list<Car> cars, TrafficLight trafficLight, int p);

	void DrawCars(HDC* hdc, RECT &rc);
	void MoveCars(HWND hWnd, RECT &rc);
};

