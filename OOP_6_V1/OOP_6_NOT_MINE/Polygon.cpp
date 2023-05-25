#include "Polygon.h"

MyPolygon::MyPolygon(HWND hWnd, int length, int speed, int rotAngle, Direction direction, int N, COLORREF color) :
    Figure(hWnd, length, speed, rotAngle, direction, color)
{
    this->N = N;
    p = new POINT[N];

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyPolygon::step() {
    Figure::step();

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyPolygon::draw(int Reg) {
    HPEN pen = CreateAndGetPen(Reg, color);
    HDC hdc;

    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, p[0].x, p[0].y, 0);

    for (int i = 1; i < N; i++) {
        LineTo(hdc, p[i].x, p[i].y);
    }

    LineTo(hdc, p[0].x, p[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}