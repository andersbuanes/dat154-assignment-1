#pragma once

#include "stdafx.h"
#include "Car.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"

class Road
{
public:
	Road(std::list<Car> cars, int p);

	void DrawCars(HDC* hdc, RECT &rc);

	int p;
	std::list<Car> cars;
	
};

