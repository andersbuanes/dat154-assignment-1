#include "TrafficLight.h"

TrafficLight::TrafficLight() {}

TrafficLight::TrafficLight(int height, int width, bool state[])
{
	this->height = height;
	this->width = width;
	this->state[0] = state[0];
	this->state[1] = state[1];
	this->state[2] = state[2];
}

void TrafficLight::ChangeState(bool state[])
{
	this->state[0] = state[0];
	this->state[1] = state[1];
	this->state[2] = state[2];
}

void TrafficLight::DrawTrafficLight(HDC* hdc, RECT& rc, bool north, bool state[])
{
	int X = rc.right / 2;
	int Y = rc.bottom / 2;
	int left, top, right, bottom, padX, padY;

	if (north)
	{
		padX = ROAD_WIDTH + width / 2;
		padY = ROAD_WIDTH + width;
		left = X - width - padX;
		top = Y - height - padY;
		right = X - padX;
		bottom = Y - padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, state[0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, state[1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, state[2] ? Colors::GREEN : Colors::GREY);

		left = X + padX;
		top = Y + padY;
		right = X + width + padX;
		bottom = Y + height + padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, state[0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, state[1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, state[2] ? Colors::GREEN : Colors::GREY);
	}
	else
	{
		padX = ROAD_WIDTH + width * 2;
		padY = ROAD_WIDTH + width / 2;
		left = X + padX;
		top = Y - height - padY;
		right = X + width + padX;
		bottom = Y - padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, state[0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, state[1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, state[2] ? Colors::GREEN : Colors::GREY);

		left = X - width - padX;
		top = Y + padY;
		right = X - padX;
		bottom = Y + height + padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, state[0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, state[1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, state[2] ? Colors::GREEN : Colors::GREY);
	}
}