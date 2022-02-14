#pragma once

#include "stdafx.h"
#include "framework.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"

class TrafficLight
{


public:
	TrafficLight(int x, int y, bool state[]);

	int x, y;
	bool state[];

	void DrawTrafficLight(HDC* hdc, RECT& rc, bool state[]);
};