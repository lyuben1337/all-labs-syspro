#pragma once

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <string>
#include "Resource.h"

using namespace std;

#pragma comment(lib, "gdi32.lib")

const int R = 200;

struct MyEllipse
{
    HANDLE hThread;
    int cx;
    int cy;
    int nap;
};

vector<MyEllipse> massEllipse;
static HANDLE hThreadPaint;

DWORD WINAPI ThreadBall(LPVOID lParam)
{
    HWND hWnd = (HWND)lParam;

    RECT rt;
    GetClientRect(hWnd, &rt);
    int Index = massEllipse.size() - 1;
    MyEllipse CurrentEllipse = massEllipse[Index];
    srand(GetTickCount64());
    CurrentEllipse.cx = rand() % (rt.right - R);
    CurrentEllipse.cy = rand() % (rt.bottom - R);
    CurrentEllipse.nap = rand() % 4 + 1;

    while (true)
    {
        if ((CurrentEllipse.cx >= rt.right - R) && (CurrentEllipse.nap == 1)) CurrentEllipse.nap = 2;
        if ((CurrentEllipse.cx <= rt.left) && (CurrentEllipse.nap == 2)) CurrentEllipse.nap = 1;
        if ((CurrentEllipse.cy >= rt.bottom - R) && (CurrentEllipse.nap == 4)) CurrentEllipse.nap = 3;
        if ((CurrentEllipse.cy <= rt.top) && (CurrentEllipse.nap == 3)) CurrentEllipse.nap = 4;
        if (CurrentEllipse.nap == 1) CurrentEllipse.cx += 5;
        if (CurrentEllipse.nap == 2) CurrentEllipse.cx -= 5;
        if (CurrentEllipse.nap == 3) CurrentEllipse.cy -= 5;
        if (CurrentEllipse.nap == 4) CurrentEllipse.cy += 5;
        massEllipse[Index] = CurrentEllipse;
        Sleep(20);
    }
}

#endif //ELLIPSE_H