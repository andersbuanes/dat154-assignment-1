#include "Road.h"

bool red[] = { TRUE, FALSE, FALSE };
bool ready[] = { TRUE, TRUE, FALSE };
bool green[] = { FALSE, FALSE, TRUE };
bool stopping[] = { FALSE, TRUE, FALSE };

Road::Road() {}

Road::Road(std::list<Car> cars, TrafficLight trafficLight, int p) : trafficLight(trafficLight)
{
	this->cars = cars;
	this->trafficLight = trafficLight;
	this->p = p;
}

void Road::DrawCars(HDC* hdc, RECT &rc)
{
	for (Car car : cars)
		car.DrawCar(*hdc, rc);
}

void Road::MoveCars(HWND hWnd, RECT &rc)
{
	std::list<Car>::iterator it;
	const auto end = cars.end();

	for (it = cars.begin(); it != end; ++it)
	{
		if (it->y > rc.bottom - 10 || it->x > rc.right - 10)
		{
			cars.erase(it);
			break;
		}
		auto it2 = it;
		it2++;
		auto next = std::find_if(it2, end, [](auto& c) { return c.direction; });
		if (next != end)
		{
			bool wouldCollideX = it->x + CAR_WIDTH + 10 >= next->x && it->y == next->y;
			bool wouldCollideY = it->y + CAR_HEIGHT + 10 >= next->y && it->x == next->x;
			
			if (wouldCollideX || wouldCollideY)
				continue;
		}
		if (trafficLight.state == green || trafficLight.state == stopping)
		{
			it->Move();
			InvalidateRect(hWnd, 0, false);
		}
		else
		{
			if (it->y < (rc.bottom / 2) - ROAD_WIDTH - 20 || it->y >(rc.bottom / 2) + ROAD_WIDTH)
			{
				it->Move();
				InvalidateRect(hWnd, 0, false);
			}
		}
	}
}