#pragma once
#include "Figure.h"

class Circle : public Figure
{
protected:
	float unnecessaryPart; // ��������, ���������� �� �������� �������� ����� ����� (��������, 1/4 ��� 1/8 � �.�.)
public:
	Circle(HWND hWnd, int length, int speed, int rotAngle, Direction direction, float unnecessaryPart, COLORREF color);
	void draw(int Reg);
};

