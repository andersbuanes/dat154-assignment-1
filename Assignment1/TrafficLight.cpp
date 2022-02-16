#include "TrafficLight.h"

TrafficLight::TrafficLight() 
{
	this->height = 0;
	this->width = 0;
	this->state = 0;
}

TrafficLight::TrafficLight(int height, int width, int state)
{
	this->height = height;
	this->width = width;
	this->state = state;
}

void TrafficLight::DrawTrafficLight(HDC* hdc, RECT& rc, bool north, int state)
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

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, LIGHTS[state][0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, LIGHTS[state][1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, LIGHTS[state][2] ? Colors::GREEN : Colors::GREY);

		// TODO remove state debug
		WCHAR text[15];
		wsprintf(text, _T("%d"), state);
		TextOut(*hdc, right, bottom, text, wcslen(text));

		left = X + padX;
		top = Y + padY;
		right = X + width + padX;
		bottom = Y + height + padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, LIGHTS[state][0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, LIGHTS[state][1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, LIGHTS[state][2] ? Colors::GREEN : Colors::GREY);
	
		// TODO remove state debug
		wsprintf(text, _T("%d"), state);
		TextOut(*hdc, right, bottom, text, wcslen(text));
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

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, LIGHTS[state][0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, LIGHTS[state][1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, LIGHTS[state][2] ? Colors::GREEN : Colors::GREY);

		// TODO remove state debug
		WCHAR text[15];
		wsprintf(text, _T("%d"), state);
		TextOut(*hdc, right, bottom, text, wcslen(text));

		left = X - width - padX;
		top = Y + padY;
		right = X - padX;
		bottom = Y + height + padY;
		RoundedRect(hdc, left, top, right, bottom, Colors::BLACK);

		Circle(hdc, left + 10, top + 10, right - 10, top + 60, LIGHTS[state][0] ? Colors::RED : Colors::GREY);
		Circle(hdc, left + 10, top + 75, right - 10, top + 125, LIGHTS[state][1] ? Colors::YELLOW : Colors::GREY);
		Circle(hdc, left + 10, top + 140, right - 10, top + 190, LIGHTS[state][2] ? Colors::GREEN : Colors::GREY);
		
		// TODO remove state debug
		wsprintf(text, _T("%d"), state);
		TextOut(*hdc, right, bottom, text, wcslen(text));
	}
}