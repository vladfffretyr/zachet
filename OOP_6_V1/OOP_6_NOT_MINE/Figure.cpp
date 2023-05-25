#include "Figure.h"

Figure::Figure(HWND hWnd, int length, int rotAngle, int speed, Direction direction, COLORREF color)
{
    this->hWnd      = hWnd;
    this->length    = length;
    this->speed     = speed;
    this->rotAngle  = rotAngle;
    this->direction = direction;
    this->color     = color;

    rotAngle = 0;
    N_Reg = 1;
    RECT rect;
    GetClientRect(hWnd, &rect);

    x = rect.right / 2;
    y = rect.bottom / 2;
}

void Figure::step()
{
    rotAngle += speed;
    if (rotAngle >= 360)
    {
        rotAngle -= 360;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);

    if (direction == HORIZONTAL)
    {
        x += speed * N_Reg;
        if (N_Reg == 1) {
            if (x + length >= rect.right) {
                N_Reg = -1;
            }

        }
        else {
            if (x - length <= 0) {
                N_Reg = 1;
            }
        }
    }

    if (direction == VERTICAL)
    {
        y += speed * N_Reg;
        if (N_Reg == 1) {
            if (y + length >= rect.bottom) {
                N_Reg = -1;
            }
        }
        else {
            if (y - length <= 0) {
                N_Reg = 1;
            }
        }
    }
}

HPEN Figure::CreateAndGetPen(int Reg, COLORREF color)
{
   return (Reg == 1) ? CreatePen(PS_SOLID, 1, color) : CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}
