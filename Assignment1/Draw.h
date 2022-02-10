#pragma once

#include "stdafx.h"
#include <list>
#include "Car.h"

void DrawTrafficLight(HDC* hdc, RECT &rc, int x, int y, bool state[]);
void DrawRoads(HDC* hdc, RECT &rc);
void DrawCar(HDC* hdc, RECT &rc, Car &car);
void DrawBitMapCar(HDC* hdc, HINSTANCE hInst, Car& car);


