#include "Road.h"

Road::Road() {}

Road::Road(std::list<Car> cars, TrafficLight trafficLight, int p) : trafficLight(trafficLight)
{
	this->cars = cars;
	this->trafficLight = trafficLight;
	this->p = p;
}

void Road::DrawCars(HDC* hdc, RECT &rc)
{
	std::list<Car>::iterator it;
	const auto end = cars.end();

	for (it = cars.begin(); it != end; ++it)
	{
		Car car = *it;
		int left = car.x - CAR_WIDTH;
		int right = car.x + CAR_WIDTH;
		int top = car.y - CAR_HEIGHT;
		int bottom = car.y + CAR_HEIGHT;
		Rect(hdc, left, top, right, bottom, RGB(rand() % 255, rand() % 255, rand() % 255));
	}
}