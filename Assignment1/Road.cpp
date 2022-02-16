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
	for (auto car : cars)
		car.DrawCar(*hdc, rc);
}

void Road::MoveCars(HWND hWnd, RECT &rc)
{
	std::list<Car>::iterator it;
	const auto end = cars.end();

	for (it = cars.begin(); it != end; ++it)
	{
		bool isFinished, wouldCollide, canMove;
		switch (it->direction) 
		{
		case NORTH:
			isFinished = it->y < 10;
			break;
		case EAST:
			isFinished = it->x > rc.right - 10;
			break;
		case SOUTH:
			isFinished = it->y > rc.bottom - 10;
			break;
		case WEST:
			isFinished = it->x < 10;
			break;
		}
		if (isFinished)
		{
			cars.erase(it);
			break;
		}
		auto next = it;
		next++;
		if (next != end)
		{
			switch (it->direction)
			{
			case NORTH:
				wouldCollide = it->y - CAR_HEIGHT - 10 <= next->y && it->x == next->x;
				break;
			case EAST:
				wouldCollide = it->x + CAR_WIDTH + 10 >= next->x && it->y == next->y;
				break;
			case SOUTH:
				wouldCollide = it->y + CAR_HEIGHT + 10 >= next->y && it->x == next->x;
				break;
			case WEST:
				wouldCollide = it->x - CAR_WIDTH - 10 <= next->x && it->y == next->y;
				break;
			}

			if (wouldCollide)
				continue;
		}
		if (trafficLight.state == 2 || trafficLight.state == 3)
		{
			it->Move();
			InvalidateRect(hWnd, 0, false);
		}
		else
		{
			// Intersection bounds
			int left = (rc.right / 2) - ROAD_WIDTH;
			int top = (rc.bottom / 2) - ROAD_WIDTH;
			int right = (rc.right / 2) + ROAD_WIDTH;
			int bottom = (rc.bottom / 2) + ROAD_WIDTH;
			switch (it->direction)
			{
			case NORTH:
				canMove = it->y > bottom			|| it->y < bottom - (CAR_HEIGHT / 2);
				break;
			case EAST:
				canMove = it->x + CAR_WIDTH < left	|| it->x + CAR_WIDTH > left + (CAR_WIDTH / 2);
				break;
			case SOUTH:
				canMove = it->y + CAR_HEIGHT < top	|| it->y + CAR_HEIGHT > top + (CAR_HEIGHT / 2);
				break;
			case WEST: 
				canMove = it->x > right				|| it->x < right - (CAR_WIDTH / 2);
				break;
			}
			if (canMove)
			{
				it->Move();
				InvalidateRect(hWnd, 0, false);
			}
		}
	}
}