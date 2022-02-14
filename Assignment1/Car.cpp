#include "Car.h"

Car::Car(int x, int y, bool direction) {
	this->x = x;
	this->y = y;
	this->direction = direction;
}

Car::~Car(){}

void Car::Move()
{
	if (direction)
	{
		y += MOVESPEED;
	}
	else {
		x += MOVESPEED;
	}
}