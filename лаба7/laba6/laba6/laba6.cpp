﻿// laba6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "laba6.h"
#include <cmath>


using namespace std;

# define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES
#define MAX_LOADSTRING 100
HANDLE hEvent;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABA6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA6));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

class Figure {
protected:
    int x, y;
    int R;
    int Ang;
    int VAng;
    int V;
    int Napr;
    COLORREF col;
    HWND hWnd;
    int N_Reg;
public:
    Figure(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    virtual void step();
    virtual void draw(int Reg) = 0;
};

Figure::Figure(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) {
    this->R = R;
    this->VAng = VAng;
    this->V = V;
    this->Napr = Napr;
    this->col = col;
    this->hWnd = hWnd;
    Ang = 0;
    N_Reg = 1;
    RECT rect;
    GetClientRect(hWnd, &rect);
    x = rect.right/2;
    y = rect.bottom/2;
}

void Figure::step() {
    Ang += VAng;
    if (Ang >= 360) Ang -= 360;
    RECT rect;
    GetClientRect(hWnd, &rect);
    if (Napr == 1) {
        x += V * N_Reg;
        if (N_Reg == 1) {
            if (x + R >= rect.right) N_Reg = -1;
        }
        else {
            if (x - R <= 0) N_Reg = 1;
        }
    }
    else {
        y += V * N_Reg;
        if (N_Reg == 1) {
            if (y + R >= rect.right) N_Reg = -1;
        }
        else {
            if (y - R <= 0) N_Reg = 1;
        }
    }
}

class MyPolygon : public Figure {
protected:
    int N;
    POINT* p;
public:
    MyPolygon(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd, int N);
    void step();
    void draw(int Reg);
};

MyPolygon::MyPolygon(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd, int N):
   Figure(R, VAng, V, Napr, col, hWnd)
{
    this->N = N;
    p = new POINT[N];
    double A = Ang * M_PI / 180;
    double A1 = 2 * M_PI / N;
    
    for (int i = 0; i < N;i++, A += A1) {
        p[i].x = x + R * cos(A);
        p[i].y = y - R * sin(A);
    }
}

void MyPolygon::step() {
    Figure::step();
    double A = (Ang+10) * M_PI / 180 +25;
    double A1 = 1.75 * M_PI / N +25;
    for (int i = 0; i < N; i++, A += A1) {
            p[i].x = x + R * cos(A);
            p[i].y = y - R * sin(A);
    }
}

void MyPolygon::draw(int Reg) {
    HPEN pen;
    if (Reg == 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
    HDC hdc;
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, p[0].x,p[0].y, 0);
    for (int i = 1; i < N;i++) LineTo(hdc, p[i].x, p[i].y);
    LineTo(hdc, p[0].x, p[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}

class MyOtrezok : public Figure {
protected:
    int x1, y1, x2, y2;
public:
    MyOtrezok(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    void step();
    void draw(int Reg);
};

MyOtrezok::MyOtrezok(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) :
    Figure(R, VAng, V, Napr, col, hWnd)
{
    double A = Ang * M_PI / 180;
    x1 = x + R * cos(A);
    x2 = x - R * cos(A);
    y1 = y + R * sin(A);
    y2 = y - R * sin(A);
}

void MyOtrezok::step() {
    Figure::step();
    double A = Ang * M_PI / 180;
    x1 = x + R * cos(A);
    x2 = x - R * cos(A);
    y1 = y + R * sin(A);
    y2 = y - R * sin(A);
}

void MyOtrezok::draw(int Reg) {
    HPEN pen;
    if (Reg == 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HDC hdc;
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, x1, y1, 0);
    LineTo(hdc, x2, y2);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}

class MyPoluKrug :public Figure {
public:
    MyPoluKrug(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    void draw(int Reg);
};

MyPoluKrug::MyPoluKrug(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) :
    Figure(R, VAng, V, Napr, col, hWnd) {}

void MyPoluKrug::draw(int Reg){
    HPEN pen;
    if (Reg == 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HDC hdc;
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, x, y, 0);
    AngleArc(hdc, x, y, R, Ang, 270);
    LineTo(hdc, x, y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}


struct ForThread
{
    Figure* pFig;
    HANDLE hEvent;
};

HANDLE hEvents[9];
Figure* pf[9];
ForThread Data[9];
int flag = 1;

DWORD WINAPI ThreadFun(LPVOID par) {
    ForThread* pData = (ForThread*)par;
    WaitForSingleObject(hEvent, INFINITE);
    while (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0) {
        pData->pFig->draw(1);
        Sleep(20);
        pData->pFig->draw(0);
        pData->pFig->step();
    }
    SetEvent(pData->hEvent);
    return 1;
}

Figure* pF[9];

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
        hEvent = CreateEvent(0,true,false, L"MyEvent1");
        pF[0] = new MyPolygon(250, 1, 10,0,RGB(255, 0, 0), hWnd, 4);
        pF[1] = new MyPolygon(150, 2, 5, 0, RGB(0, 255, 0), hWnd, 3);
        pF[2] = new MyPolygon(70, 3, 3, 1, RGB(0, 0, 255), hWnd, 3);
        pF[3] = new MyOtrezok(50, 4, 2, 1, RGB(255, 0, 255), hWnd);
        pF[4] = new MyOtrezok(100, 2, 1, 1, RGB(0, 255, 255), hWnd);
        pF[5] = new MyOtrezok(150, 1, 2, 0, RGB(0, 0, 255), hWnd);
        pF[6] = new MyPoluKrug(50, 2, 2, 0, RGB(255, 0, 255), hWnd);
        pF[7] = new MyPoluKrug(100, 1, 3, 0, RGB(0, 255, 255), hWnd);
        pF[8] = new MyPoluKrug(150, 3, 4, 1, RGB(0, 0, 255), hWnd);

        for (int i = 0; i < 9; i++)
        {
            Data[i].pFig = pF[i];
            Data[i].hEvent = hEvents[i] = CreateEvent(0, false, false, 0);
            CreateThread(0,0,ThreadFun, &Data[i], 0, 0);
        }
        break;
    case WM_COMMAND:
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                flag = 0;
                WaitForMultipleObjects(9,hEvents,TRUE,INFINITE);
                for (int i = 0; i < 9; i++)
                {
                    delete pF[i];
                    CloseHandle(hEvents[i]);
                }
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        flag = 0;
        WaitForMultipleObjects(9, hEvents, TRUE, INFINITE);
        for (int i = 0; i < 9; i++)
        {
            delete pF[i];
            CloseHandle(hEvents[i]);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
