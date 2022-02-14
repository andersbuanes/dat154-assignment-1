#pragma once

#define MOVESPEED 3;

class Car
{
public:
	Car(int x, int y, bool direction);
	~Car();

	void Move();

	int x;
	int y;
	bool direction; // true if driving south or east, else false
};

