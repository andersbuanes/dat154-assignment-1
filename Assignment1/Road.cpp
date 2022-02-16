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
	// TODO fix light stop position/condition
	std::list<Car>::iterator it;
	const auto end = cars.end();

	for (it = cars.begin(); it != end; ++it)
	{
		bool isFinished = false, wouldCollide = true, canMove = false;
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
			// TODO fix collision detection
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
		if (trafficLight.state == green || trafficLight.state == stopping)
		{
			it->Move();
			InvalidateRect(hWnd, 0, false);
		}
		else
		{
			int X = rc.right / 2;
			int Y = rc.bottom / 2;
			switch (it->direction)
			{
			case NORTH:
				canMove = it->y > Y + ROAD_WIDTH || it->y < Y - ROAD_WIDTH;
				break;
			case EAST:
				canMove = it->x < X - ROAD_WIDTH - CAR_WIDTH || it->x > X + ROAD_WIDTH;
				break;
			case SOUTH:
				canMove = it->y < Y - ROAD_WIDTH - CAR_HEIGHT || it->y > Y + ROAD_WIDTH;
				break;
			case WEST: 
				canMove = it->x > X - ROAD_WIDTH || it->x < X - ROAD_WIDTH;
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