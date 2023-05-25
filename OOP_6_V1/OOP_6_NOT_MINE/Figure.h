#pragma once
#include "framework.h"

enum Direction {
    VERTICAL,
    HORIZONTAL
};

class Figure
{
protected:
    int x, y;
    int length;
    int rotAngle;
    int speed;
    Direction direction;
    COLORREF color;
    HWND hWnd;
    int N_Reg;
public:
    Figure(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF color);

    virtual void step();
    virtual void draw(int Reg) = 0;
protected:
    HPEN CreateAndGetPen(int Reg, COLORREF color);
};