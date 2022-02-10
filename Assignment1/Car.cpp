#include "Car.h"

Car::Car(int x, int y, int speed, bool direction) {
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->direction = direction;
}

Car::~Car(){}

void Car::Move()
{
	if (direction)
	{
		y += speed;
	}
	else {
		x += speed;
	}
}