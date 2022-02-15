#pragma once

#include "stdafx.h"
#include "framework.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"

class TrafficLight
{
public:
	int height, width;
	bool state[3];
	
	TrafficLight();
	TrafficLight(int height, int width, bool state[]);

	void ChangeState(bool state[]);
	void DrawTrafficLight(HDC* hdc, RECT& rc, bool north, bool state[]);
};