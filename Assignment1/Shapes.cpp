#include "Shapes.h"
#include "stdafx.h"

void Rect(HDC* hdc, int left, int top, int right, int bottom, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HGDIOBJ hOrg = SelectObject(*hdc, hBrush);
	RECT rc;
	rc.left = left;
	rc.top = top;
	rc.right = right;
	rc.bottom = bottom;
	RoundRect(*hdc, left, top, right, bottom, 10, 10);
	//FillRect(*hdc, &rc, hBrush);
	SelectObject(*hdc, hOrg);
	DeleteObject(hBrush);
	DeleteObject(hOrg);
}

void Circle(HDC* hdc, int left, int top, int right, int bottom, COLORREF color) 
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HGDIOBJ hOrg = SelectObject(*hdc, hBrush);
	Ellipse(*hdc, left, top, right, bottom);
	SelectObject(*hdc, hOrg);
	DeleteObject(hBrush);
	DeleteObject(hOrg);
}

void Line(HDC* hdc, int left, int top, int right, int bottom, COLORREF color)
{
	LOGBRUSH lb;
	lb.lbColor = color;
	lb.lbStyle = PS_SOLID;

	HGDIOBJ hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);
	HGDIOBJ hPenOld = SelectObject(*hdc, hPen);

	MoveToEx(*hdc, left, top, 0);
	LineTo(*hdc, right, bottom);

	SelectObject(*hdc, hPenOld);
	DeleteObject(hPen);
	DeleteObject(hPenOld);
}