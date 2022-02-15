#pragma once

#include "stdafx.h"
#include "Constants.h"
#include "Shapes.h"
#include "Direction.h"

#define MOVESPEED 3;

class Car
{
public:
	int x;
	int y;
	Direction direction; // true if driving south or east, else false
	COLORREF color;

	Car(int x, int y, Direction direction, COLORREF color);
	~Car();

	void Move();
	void DrawCar(HDC hdc, RECT &rc);

};

