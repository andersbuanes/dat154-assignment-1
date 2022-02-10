#pragma once

#define MOVESPEED 3;

class Car
{
public:
	Car(int x, int y, int speed, bool direction);
	~Car();

	void Move();

	int x;
	int y;
	int speed;
	bool direction; // true if driving south, else false
};

