#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Figure.h";

class MyPolygon : public Figure
{
protected:
    int N;
    POINT* p;
public:
    MyPolygon(HWND hWnd, int length, int speed, int rotAngle, Direction direction, int N, COLORREF color);
    void step();
    void draw(int Reg);
};

