// AllLabsWinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AllLabsWinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HCURSOR cursor;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Authors(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Time(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Closing(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ReadText(HWND, UINT, WPARAM, LPARAM);
int labNumber;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ALLLABSWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ALLLABSWINAPI));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(NULL, IDI_INFORMATION);
    wcex.hCursor        = LoadCursor(nullptr, IDC_WAIT);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ALLLABSWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = NULL;

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   int screenX = 800;
   int screenY = 500;

   HWND hWnd = CreateWindow(
       szWindowClass,   // ім’я класу вікна
       szTitle, // назва програми
       WS_OVERLAPPEDWINDOW | WS_VSCROLL,    // стиль вікна
       (GetSystemMetrics(SM_CXSCREEN) - screenX) / 2, // положення по Х
       (GetSystemMetrics(SM_CYSCREEN) - screenY) / 2, // положення по Y  
       screenX,       // розмір по Х
       screenY,       // розмір по Y
       NULL,           // дескриптор батьківського вікна  
       NULL,           // дескриптор меню вікна
       hInstance,         // дескриптор програми
       NULL
   );         // параметри створення.

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_AUTHORS:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_AUTHORBOX), hWnd, Authors);
                break;
            case IDM_TIME:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TIME), hWnd, Time);
                break;
            case ID_CURSORE_CURSORE1:
                cursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
                SetCursor(cursor);
                break;
            case ID_CURSORE_CURSORE2:
                cursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
                SetCursor(cursor);
                break;
            case ID_CURSORE_CURSORE3:
                cursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR3));
                SetCursor(cursor);
                break;
            case ID_LABS_1_READTEXT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_READ), hWnd, ReadText);
                break;
            case ID_LABS_2:
                labNumber = 2;
                break;   
            case ID_LABS_3:
                labNumber = 3;
                break;   
            case ID_LABS_4:
                labNumber = 4;
                break;   
            case ID_LABS_5:
                labNumber = 5;
                break;   
            case ID_LABS_6:
                labNumber = 6;
                break;   
            case ID_LABS_7:
                labNumber = 7;
                break;   
            case ID_LABS_8:
                labNumber = 8;
                break;
            case ID_LABS_9:
                labNumber = 9;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            if (GetCursor() != NULL) {
                return TRUE;
            }
        }
        break;
    case WM_CLOSE:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_CLOSE), hWnd, Closing);
        break;
    case WM_DESTROY:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

// Message handler for authors box.
INT_PTR CALLBACK Authors(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// Message handler for timer box.
INT_PTR CALLBACK Time(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SYSTEMTIME time;
    wchar_t timeString[9]; // Формат времени: HH:MM:SS
    RECT timeRect;
    GetClientRect(hDlg, &timeRect);
    // Получение текущего времени
    GetLocalTime(&time);
    // Преобразование времени в строку
    swprintf_s(timeString, 9, L"%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetTimer(hDlg, 1, 100, NULL);
        return (INT_PTR)TRUE;
    case WM_TIMER:
        if (wParam == 1) {
            // Получение текущего времени
            GetLocalTime(&time);
            // Преобразование времени в строку
            swprintf_s(timeString, 9, L"%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
            InvalidateRect(hDlg, &timeRect, TRUE);
        }
        break;
    case WM_PAINT: {
        // Создание шрифта размером 16
        HFONT font = CreateFont(
            64,                 // высота шрифта
            0,                  // ширина символов
            0,                  // угол наклона шрифта
            0,                  // угол поворота шрифта
            FW_NORMAL,          // толщина шрифта
            FALSE,              // курсивный шрифт
            FALSE,              // подчеркнутый шрифт
            FALSE,              // зачеркнутый шрифт
            DEFAULT_CHARSET,    // набор символов
            OUT_DEFAULT_PRECIS, // точность вывода
            CLIP_DEFAULT_PRECIS,// точность отсечения
            DEFAULT_QUALITY,    // качество вывода
            DEFAULT_PITCH,      // шаг
            L"Arial"            // имя шрифта
        );
        // Выбор шрифта в контексте устройства
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hDlg, &ps);
        SetBkMode(hdc, TRANSPARENT);
        HFONT oldFont = (HFONT)SelectObject(hdc, font);
        DrawText(hdc, timeString, -1, &timeRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        DeleteObject(font);
        EndPaint(hDlg, &ps);
        break;
    }
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

INT_PTR CALLBACK Closing(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_TIMER:
        KillTimer(hDlg, 2); // Останавливаем таймер
        PostQuitMessage(0); // Посылаем сообщение о завершении приложения
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDOK)
        {
            SetTimer(hDlg, 2, 2000, NULL); // Запускаем таймер на 3 секунды
            EnableWindow(GetDlgItem(hDlg, IDOK), FALSE); // Блокируем кнопку "ОК"
            EnableWindow(GetDlgItem(hDlg, IDCANCEL), FALSE); // Блокируем кнопку "Отмена"
            MessageBox(hDlg, L"Window is closing in 2 seconds", L"Attention!", FALSE);
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ReadText(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDOK)
        {
            wchar_t s_text_1[255];
            GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), s_text_1, 255);
            MessageBox(hDlg, s_text_1, L"Text", FALSE);
        }
        break;
    }
    return (INT_PTR)FALSE;
}
