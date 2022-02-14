#pragma once

#include "stdafx.h"
#include "framework.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"

class TrafficLight
{

public:
	int x, y;
	bool state[3];
	
	TrafficLight();
	TrafficLight(int x, int y, bool state[]);

	void ChangeState(bool state[]);
	void DrawTrafficLight(HDC* hdc, RECT& rc, bool state[]);
};