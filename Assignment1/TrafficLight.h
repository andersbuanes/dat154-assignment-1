#pragma once

#include "stdafx.h"
#include "framework.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"

class TrafficLight
{
public:
	int height, width, state;
	
	TrafficLight();
	TrafficLight(int height, int width, int state);

	void DrawTrafficLight(HDC* hdc, RECT& rc, bool north, int state);
};