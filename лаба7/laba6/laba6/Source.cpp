#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <locale.h>

using namespace std;

int main() {
	HANDLE hEvent;
	setlocale(LC_ALL,"rus");
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"MyEvent1");
	if (hEvent == 0) {
		cout << "������ �������� �������, ���������� � ������ ����������";
		_getch();
		return 0;
	}
	cout << "��� ������� ������� � ������ ���������� ������� ����� �������" << endl;
	_getch();
	SetEvent(hEvent);
	cout << "��� ���������� ������� ������� ����� �������" << endl;
	_getch();
	ResetEvent(hEvent);
	cout << "��� ���������� ������� ����� �������" << endl;
	_getch();
	return 0;
}