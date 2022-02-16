#pragma once

#include "stdafx.h"
#include "Constants.h"
#include "Shapes.h"
#include "Direction.h"

#define MOVESPEED 2;

class Car
{
public:
	int x;
	int y;
	Direction direction;
	COLORREF color;

	Car(int x, int y, Direction direction, COLORREF color);
	~Car();

	void Move();
	void DrawCar(HDC hdc, RECT &rc);
};

