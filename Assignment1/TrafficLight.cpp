#include "TrafficLight.h"

const bool redState[] = { TRUE, FALSE, FALSE };
const bool readyState[] = { TRUE, TRUE, FALSE };
const bool greenState[] = { FALSE, FALSE, TRUE };
const bool stoppingState[] = { FALSE, TRUE, FALSE };

TrafficLight::TrafficLight(int x, int y, bool state[])
{
	this->x = x;
	this->y = y;
	this->state = state;
}

void TrafficLight::DrawTrafficLight(HDC* hdc, RECT& rc, bool state[])
{
	int width = 90;
	int height = 250;

	int left = (rc.right / 2) - width + x;
	int top = (rc.bottom / 2) - height + y;

	int right = left + 90;
	int bottom = top + 250;

	int fTop = top + 10;
	int sTop = top + 90;
	int tTop = top + 170;

	// Draw background
	Rect(hdc, left, top, right, bottom, Colors::BLACK);

	// Draw circles (conditional)
	Circle(hdc, left + 10, fTop, right - 10, top + 80, state[0] ? Colors::RED : Colors::GREY);
	Circle(hdc, left + 10, sTop, right - 10, top + 160, state[1] ? Colors::YELLOW : Colors::GREY);
	Circle(hdc, left + 10, tTop, right - 10, top + 240, state[2] ? Colors::GREEN : Colors::GREY);
}