#include <stdlib.h>
#include <algorithm>
#include <list>

#include "Draw.h"
#include "Shapes.h"
#include "Car.h"
#include "Colors.h"
#include "Resource.h"

/*
	Traffic Light States:
	0 - red
	1 - ready
	2 - green
	3 - stopping
*/
using namespace Colors;
void DrawTrafficLight(HDC* hdc, RECT &rc, int x, int y, bool state[])
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
	Rect(hdc, left, top, right, bottom, BLACK);

	Circle(hdc, left + 10, fTop, right - 10, top + 80, state[0] ? RED : GREY);
	Circle(hdc, left + 10, sTop, right - 10, top + 160, state[1] ? YELLOW : GREY);
	Circle(hdc, left + 10, tTop, right - 10, top + 240, state[2] ? GREEN : GREY);

}

void DrawRoads(HDC* hdc, RECT &rc)
{

	int centerX = rc.right / 2;
	int centerY = rc.bottom / 2;
	int width = 50; // width of each side of the road

	// Draw roads
	Rect(hdc, 10, centerY - width, rc.right - 10, centerY + width, ASPHALTGREY); // west to east
	Rect(hdc, centerX - width, 10, centerX + width, rc.bottom - 10, ASPHALTGREY); // north to south

	// Draw lane dividers west to east
	Line(hdc, 10, centerY, rc.right - 10, centerY, DIVIDERYELLOW);

	// Draw lane dividers north to south
	Line(hdc, centerX, 10, centerX, rc.bottom - 10, DIVIDERYELLOW);

	// Draw crossing center
	Rect(hdc, centerX - width, centerY - width, centerX + width, centerY + width, ASPHALTGREY);
}

void DrawCar(HDC* hdc, RECT &rc, Car &car)
{
	int left = car.x - 20;
	int right = car.x + 20;
	int top = car.y - 20;
	int bottom = car.y + 20;

	Rect(hdc, left, top, right, bottom, BLACK);
}

/*
void DrawBitMapCar(HDC* hdc, HINSTANCE hInst, Car &car)
{
	HDC hdcMem = CreateCompatibleDC(*hdc);

	HBITMAP bm = CreateCompatibleBitmap(*hdc, car.width + 50, car.height + 50);

	SelectObject(hdcMem, bm);

	HDC hdcCar = CreateCompatibleDC(*hdc);

	HBITMAP bmCar = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	SelectObject(hdcCar, bmCar);

	BitBlt(hdcMem, car.x, car.y, 200, 500, hdcCar, 0, 0, SRCCOPY);

	BitBlt(*hdc, 0, 0, 1000, 1000, hdcMem, 0, 0, SRCCOPY);

	DeleteDC(hdcCar);
	DeleteDC(hdcMem);
	DeleteObject(bm);
	DeleteObject(bmCar);
}
*/