#include "Car.h"

Car::Car(int x, int y, Direction direction, COLORREF color) {
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->color = color;
}

Car::~Car(){}

void Car::Move()
{
	switch (direction)
	{
	case NORTH:
		y -= MOVESPEED;
		break;
	case EAST:
		x += MOVESPEED;
		break;
	case SOUTH:
		y += MOVESPEED;
		break;
	case WEST:
		x -= MOVESPEED;
		break;
	}
}

void Car::DrawCar(HDC hdc, RECT &rc)
{
	Rect(&hdc, x, y, x +CAR_WIDTH, y + CAR_WIDTH, color);
	// TODO remove state debug
	WCHAR text[15];
	wsprintf(text, _T("%d"), x);
	TextOut(hdc, x, y, text, wcslen(text));
}