// AllLabsWinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AllLabsWinAPI.h"
#include "ellipse.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HCURSOR cursor;
int screenX = 800;
int screenY = 500;
WINGDIAPI BOOL WINAPI DrawRandomCircle(HDC, POINT);
typedef BOOL(WINAPI* PFN) (HDC, LPARAM);
static HINSTANCE hLibrary;
static PFN mouseRect;
HDC				hdc;
PAINTSTRUCT		ps;
HBITMAP			hBitmap;
static HDC		memBit;
static POINT	pt;
static POINT	s;
SYSTEMTIME		tm;
RECT clientRect;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Authors(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Time(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Closing(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ReadText(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI        ThreadPaint(LPVOID lParam);
std::string         GenerateUniqueName(bool flag);
bool                deleteAllFile(TCHAR* dir, TCHAR* path, bool atribute);
int                 division(int a, int b);
int                 substraction(int a, int b);
void                binaryString(int num, char* str);



int labNumber;
void lab2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab5(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HANDLE& hTreadPaint, STARTUPINFO& tin, PROCESS_INFORMATION& pInfo, DWORD& exitCode);
void lab6(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab7(HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam,
    PFN& mouseRect,
    HDC& memBit,
    POINT& pt,
    POINT& s,
    SYSTEMTIME& tm,
    HDC hdc);
void lab8(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab9(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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

   HWND hWnd = CreateWindow(
       szWindowClass,   // ім’я класу вікна
       szTitle, // назва програми
       WS_OVERLAPPEDWINDOW | WS_VSCROLL,   // стиль вікна
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
    static HANDLE hThreadPaint;
    static STARTUPINFO tin;
    static PROCESS_INFORMATION pInfo;
    static DWORD exitCode;

    switch (labNumber)
    {
    case 2:
        lab2(hWnd, message, wParam, lParam);
        break;
    case 3:
        lab3(hWnd, message, wParam, lParam);
        break;
    case 4:
        lab4(hWnd, message, wParam, lParam);
        break;
    case 5:
        lab5(hWnd, message, wParam, lParam, hThreadPaint, tin, pInfo, exitCode);
        break;
    case 6:
        lab6(hWnd, message, wParam, lParam);
        break;
    case 7:
        switch (message)
        {
        case WM_TIMER:
            DrawRandomCircle(memBit, s);
            InvalidateRect(hWnd, NULL, 0);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            s.x = clientRect.right;
            s.y = clientRect.bottom;
            BitBlt(hdc, 0, 0, s.x, s.y, memBit, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            break;
        case WM_LBUTTONUP:
            mouseRect(memBit, lParam);
            InvalidateRect(hWnd, NULL, 0);
            break;
        default:
            break;
        }
        break;
    case 8:
        break;
    case 9:
        break;
    default:
        break;
    }
    switch (message)
    {
    case WM_CREATE:
        tin.cb = sizeof(STARTUPINFO);
        tin.dwFlags = STARTF_USESHOWWINDOW;
        tin.wShowWindow = SW_SHOWNORMAL;
        hThreadPaint = CreateThread(NULL, 0, ThreadPaint, (LPVOID)hWnd, 0, NULL);
        hLibrary = LoadLibrary(L"sisPro6Dll");
        GetClientRect(hWnd, &clientRect);
        if (hLibrary)
        {
            mouseRect = (PFN)GetProcAddress(hLibrary, "DrawMouseRect");
            if (mouseRect == NULL)
            {
                MessageBox(hWnd, _T("Функция Triangle не найдена"),
                    _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);
                DestroyWindow(hWnd);
                return 0;
            }
        }
        else
        {
            DestroyWindow(hWnd);
            return 0;
        }
        SetTimer(hWnd, 1, 100, NULL);
        pt.x = GetSystemMetrics(SM_CXSCREEN);
        pt.y = GetSystemMetrics(SM_CYSCREEN);
        hdc = GetDC(hWnd);
        memBit = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, pt.x, pt.y);
        SelectObject(memBit, hBitmap);
        PatBlt(memBit, 0, 0, pt.x, pt.y, WHITENESS);
        ReleaseDC(hWnd, hdc);
        GetSystemTime(&tm);
        srand(tm.wMilliseconds);
        break;
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
            case ID_LABS_1:
                InvalidateRect(hWnd, NULL, TRUE);
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
                screenX = 800;
                screenY = 600;
                InvalidateRect(hWnd, NULL, TRUE);
                break;   
            case ID_LABS_3:
                labNumber = 3;
                screenX = 650;
                screenY = 400;
                InvalidateRect(hWnd, NULL, TRUE);
                break;   
            case ID_LABS_4_ELIPSE:
                if (labNumber != 4) {
                    labNumber = 4;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab4(hWnd, message, wParam, lParam);
                }
                break;
            case ID_LABS_4_LINE:
                if (labNumber != 4) {
                    labNumber = 4;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab4(hWnd, message, wParam, lParam);
                }
                break;
            case ID_LABS_4_SQUARE:
                if (labNumber != 4) {
                    labNumber = 4;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab4(hWnd, message, wParam, lParam);
                }
                break;
            case ID_LABS_5_ELIPSE:
                if (labNumber != 5) {
                    labNumber = 5;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab5(hWnd, message, wParam, lParam, hThreadPaint, tin, pInfo, exitCode);
                }
                break;
            case ID_PROCESSES_CREATEPROCESS:
                if (labNumber != 5) {
                    labNumber = 5;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab5(hWnd, message, wParam, lParam, hThreadPaint, tin, pInfo, exitCode);
                }
                break;
            case ID_PROCESSES_DELETEPROCESS:
                if (labNumber != 5) {
                    labNumber = 5;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab5(hWnd, message, wParam, lParam, hThreadPaint, tin, pInfo, exitCode);
                }
                break;
            case ID_FILE_COPY:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_FILE_CREATE:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_FILE_INFO:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_FILE_MOVETOANOTHERLOGICDISK:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_FILE_OPEN:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_FILE_SAVE:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_TYPESDELETING_DOCX:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_TYPESDELETING_HIDDEN:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_TYPESDELETING_TXT:
                if (labNumber != 6) {
                    labNumber = 6;
                    screenX = 800;
                    screenY = 500;
                    InvalidateRect(hWnd, NULL, TRUE);
                    lab6(hWnd, message, wParam, lParam);
                }
                break;
            case ID_LABS_7:
                labNumber = 7;
                break;   
            case ID_LABS_8: {
                    /*labNumber = 8;
                    int a;
                    char out[33];
                    binaryString(a, out);
                    std::string myStdString(out);
                    std::wstring myWideString(myStdString.begin(), myStdString.end());*/
                MessageBox(hWnd, L"XUI", NULL, NULL);
            }
            break;
            case ID_LABS_9:
                labNumber = 9;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            SetWindowPos(hWnd,
                NULL,
                (GetSystemMetrics(SM_CXSCREEN) - screenX) / 2,
                (GetSystemMetrics(SM_CYSCREEN) - screenY) / 2,
                screenX,
                screenY,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
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
        GetExitCodeProcess(pInfo.hProcess, &exitCode);
        if (exitCode == STILL_ACTIVE) TerminateProcess(pInfo.hProcess, 0);
        for (int i = 0; i < massEllipse.size(); i++) {
            CloseHandle(massEllipse[i].hThread);
        }
        FreeLibrary(hLibrary);
        DeleteObject(memBit);
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

DWORD WINAPI ThreadPaint(LPVOID lParam)
{
    HWND hWnd = (HWND)lParam;
    while (true)
    {
        if (labNumber == 5) {
            InvalidateRect(hWnd, NULL, TRUE);
            Sleep(20);
        }
    }
    return 0;
}

std::string GenerateUniqueName(bool flag)
{
    DWORD ticks = GetTickCount64();
    std::string name = (flag ? "File" : "Copy") + std::to_string(ticks);
    return name;
}

bool deleteAllFile(TCHAR* dir, TCHAR* path, bool atribute)
{
    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile(path, &fileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;
    do
    {
        TCHAR filePath[256];
        wsprintf(filePath, TEXT("%s\\%s"), dir, fileData.cFileName);
        if (atribute)
        {
            if (fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
            {
                SetFileAttributes(filePath, FILE_ATTRIBUTE_NORMAL);
                if (!DeleteFile(filePath))
                    return 0;

            }
        }
        else
        {
            SetFileAttributes(filePath, FILE_ATTRIBUTE_NORMAL);
            if (!DeleteFile(filePath))
                return 0;
        }

    } while (FindNextFile(hFind, &fileData));

    FindClose(hFind);

    return 1;

}

void lab2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    TEXTMETRIC tm;
    static PTCHAR msg = (PTCHAR)GlobalAlloc(GPTR, 100 * sizeof(TCHAR));
    static wchar_t Strings[100][100];
    static int countStrings = 0;
    static int sizeMsg = 0;
    wchar_t debugString[32];
    static int x = 0, y = 0;
    switch (message) {
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        GetTextMetrics(hdc, &tm);

        TextOut(hdc, x, y, msg, sizeMsg);
        for (int i = 0; i < 10; i++) {
            TextOut(hdc, 250, i * 20, (LPCWSTR)Strings[i], size(Strings[i]));
        }

        wchar_t out[32];
        TextOut(hdc, 250, 300, (LPCWSTR)out, wsprintf(out, L"ICON X: %d\0", GetSystemMetrics(SM_CXICON)));
        TextOut(hdc, 250, 320, (LPCWSTR)out, wsprintf(out, L"ICON Y: %d\0", GetSystemMetrics(SM_CYICON)));
        TextOut(hdc, 250, 360, (LPCWSTR)out, wsprintf(out, L"BORDER WIDTH: %d\0", GetSystemMetrics(SM_CXBORDER)));
        TextOut(hdc, 250, 400, (LPCWSTR)out, wsprintf(out, L"SCREEN X: %d\0", GetDeviceCaps(hdc, HORZRES)));
        TextOut(hdc, 250, 420, (LPCWSTR)out, wsprintf(out, L"SCREEN Y: %d\0", GetDeviceCaps(hdc, VERTRES)));
        TextOut(hdc, 250, 460, (LPCWSTR)out, wsprintf(out, L"FONT HEIGHT: %d\0", tm.tmHeight));
        TextOut(hdc, 250, 480, (LPCWSTR)out, wsprintf(out, L"LINE SPACING: %d\0", tm.tmInternalLeading));
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CHAR: {
        switch (wParam) {
        case VK_RETURN:
            if (countStrings == 10) {
                for (int i = 0; i < 9; i++) {
                    int j = 0;
                    for (; j < size(Strings[i]) || j < size(Strings[i + 1]); j++) {
                        Strings[i][j] = Strings[i + 1][j];
                    }
                    Strings[i][j] = '\0';
                }
                for (int i = 0; Strings[9][i]; i++) {
                    Strings[9][i] = '\0';
                }
                countStrings--;
            }
            for (int i = 0; i < sizeMsg; i++) {
                Strings[countStrings][i] = msg[i];
            }
            countStrings++;
            sizeMsg = 0;
            break;
        default:
            if (sizeMsg >= 100) {
                MessageBox(hWnd, L"Out of string", L"Warning!", MB_OK | MB_ICONASTERISK);
                break;
            }
            msg[sizeMsg] = (wchar_t)wParam;
            sizeMsg++;
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
                break;
    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON) {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDBLCLK:
        MessageBox(hWnd, L"D CLICK", NULL, NULL);
        break;
    }
}

void lab3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HFONT hFont;
    HDC hdc;
    RECT rt;
    HPEN hpen;
    HBRUSH hbrush;
    tagPOINT points[5];
    static LOGFONT lf; //создаём экземпляр LOGFONT
    lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
    lf.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
    strcpy_s((char*)lf.lfFaceName, LF_FACESIZE, "Times New Roman");
    lf.lfEscapement = 0; //шрифт без поворота

    int width;
    int height;
    int kegel;

    switch (message)
    {
    case WM_PAINT: //Перемалювати вікно
        hdc = BeginPaint(hWnd, &ps); //Почати графічний вивід
        GetClientRect(hWnd, &rt); //Область вікна для малювання

        hbrush = CreateSolidBrush(RGB(185, 185, 185));
        hpen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(hdc, hbrush);
        SelectObject(hdc, hpen);

        width = rt.right - rt.left;
        height = rt.bottom - rt.top;

        points[0].x = width / 2 - width / 4.8;
        points[0].y = height / 2 - height / 18;
        points[1].x = width / 2;
        points[1].y = height / 2 - height / 7.2;
        points[2].x = width / 2 + width / 4.8;
        points[2].y = height / 2 - height / 18;
        points[3].x = width / 2 + width / 4.8;
        points[3].y = height / 2 + height / 9;
        points[4].x = width / 2 - width / 4.8;
        points[4].y = height / 2 + height / 9;

        Polygon(hdc, points, 5);
        DeleteObject(hbrush);
        DeleteObject(hpen);
        hbrush = CreateSolidBrush(RGB(16, 60, 84));
        hpen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
        SelectObject(hdc, hbrush);
        SelectObject(hdc, hpen);

        Ellipse(hdc, width / 2 - width / 4.8, height / 2 - height / 9, width / 2 + width / 4.8, height / 2 + height / 9);

        DeleteObject(hbrush);
        DeleteObject(hpen);

        SetBkMode(hdc, TRANSPARENT);
        lf.lfHeight = height / 22.5; //высота
        lf.lfWidth = width / 60; //ширина
        lf.lfWeight = 20; //толщина
        kegel = width / 35;

        hFont = CreateFontIndirect(&lf);
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(255, 0, 0));

        TextOut(hdc, width / 2 - kegel * 2 - lf.lfWeight / 2, height / 2 - lf.lfHeight / 2, L"D", 1);

        SetTextColor(hdc, RGB(225, 225, 0));

        TextOut(hdc, width / 2 - kegel - lf.lfWeight / 2, height / 2 - lf.lfHeight / 2, L"O", 1);

        SetTextColor(hdc, RGB(0, 255, 0));

        TextOut(hdc, width / 2 - lf.lfWeight / 2, height / 2 - lf.lfHeight / 2, L"T", 1);

        SetTextColor(hdc, RGB(0, 0, 255));

        TextOut(hdc, width / 2 + kegel - lf.lfWeight / 2, height / 2 - lf.lfHeight / 2, L"A", 1);

        SetTextColor(hdc, RGB(255, 0, 255));

        TextOut(hdc, width / 2 + kegel * 3 - lf.lfWeight / 2, height / 2 - lf.lfHeight / 2, L"3", 1);


        DeleteObject(hFont);
        EndPaint(hWnd, &ps); //Закінчити графічний вивід
        break;
    case WM_DESTROY: //Завершення роботи
        PostQuitMessage(0);
        break;
    }
}

void lab4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    static HPEN pen;
    static RECT rc;
    static HDC hdc;
    POINT ptClientUL;
    POINT ptClientLR;
    static POINTS ptsBegin;
    static POINTS ptsEnd;
    static POINTS ptsPrevEnd;
    static BOOL fPrevLine = FALSE;

    static bool isLine = 0;
    static bool isRect = 0;
    static bool isEll = 0;

    switch (message)
    {
    case WM_SIZE: {
        SCROLLINFO scrInfo;
        scrInfo.cbSize = sizeof(SCROLLINFO);

        scrInfo.nPage = HIWORD(lParam); //размер страницы устанавливаем равным высоте окна

        scrInfo.nMin = 0; //диапазон прокрутки устанавливаем по размеру содержимого
        scrInfo.nMax = 1100; //(вместо CONTENT_HEIGHT подставь нужное значение)

        scrInfo.fMask = SIF_ALL; //применяем новые параметры
        SetScrollInfo(hWnd, SB_VERT, &scrInfo, TRUE);

        scrInfo.nMin = 0; //диапазон прокрутки устанавливаем по размеру содержимого
        scrInfo.nMax = 1200; //(вместо CONTENT_HEIGHT подставь нужное значение)

        SetScrollInfo(hWnd, SB_HORZ, &scrInfo, TRUE);
    }
                break;
    case WM_VSCROLL: {
        SCROLLINFO scrInfo;
        scrInfo.cbSize = sizeof(SCROLLINFO);

        scrInfo.fMask = SIF_ALL; //получаем текущие параметры scrollbar-а
        GetScrollInfo(hWnd, SB_VERT, &scrInfo);

        int currentPos = scrInfo.nPos; //запоминаем текущее положение содержимого

        switch (LOWORD(wParam)) { //определяем действие пользователя и изменяем положение
        case SB_LINEUP: //клик на стрелку вверх
            scrInfo.nPos -= 1;
            break;
        case SB_LINEDOWN: //клик на стрелку вниз 
            scrInfo.nPos += 1;
            break;
        case SB_THUMBTRACK: //перетаскивание ползунка
            scrInfo.nPos = scrInfo.nTrackPos;
            break;
        default:
            break;//все прочие действия (например нажатие PageUp/PageDown) игнорируем
        }

        scrInfo.fMask = SIF_POS; //пробуем применить новое положение
        SetScrollInfo(hWnd, SB_VERT, &scrInfo, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &scrInfo); //(см. примечание ниже)

        int yScroll = -currentPos + scrInfo.nPos;
        ScrollWindow(hWnd, 0, yScroll, NULL, NULL); //выполняем прокрутку
    }
                   break;
    case WM_HSCROLL: {
        SCROLLINFO scrInfo;
        scrInfo.cbSize = sizeof(SCROLLINFO);

        scrInfo.fMask = SIF_ALL; //получаем текущие параметры scrollbar-а
        GetScrollInfo(hWnd, SB_HORZ, &scrInfo);

        int currentPos = scrInfo.nPos; //запоминаем текущее положение содержимого

        switch (LOWORD(wParam)) { //определяем действие пользователя и изменяем положение
        case SB_LINEUP: //клик на стрелку вверх
            scrInfo.nPos -= 1;
            break;
        case SB_LINEDOWN: //клик на стрелку вниз 
            scrInfo.nPos += 1;
            break;
        case SB_THUMBTRACK: //перетаскивание ползунка
            scrInfo.nPos = scrInfo.nTrackPos;
            break;
        default:
            break; //все прочие действия (например нажатие PageUp/PageDown) игнорируем
        }

        scrInfo.fMask = SIF_POS; //пробуем применить новое положение
        SetScrollInfo(hWnd, SB_HORZ, &scrInfo, TRUE);
        GetScrollInfo(hWnd, SB_HORZ, &scrInfo); //(см. примечание ни
        int xScroll = -currentPos + scrInfo.nPos;
        ScrollWindow(hWnd, xScroll, 0, NULL, NULL); //выполняем прокрутку
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_LABS_4_LINE:
        {
            isLine = 1;
            isRect = 0;
            isEll = 0;
            break;
        }
        case ID_LABS_4_SQUARE:
        {
            isLine = 0;
            isRect = 1;
            isEll = 0;
            break;
        }
        case ID_LABS_4_ELIPSE:
        {
            isLine = 0;
            isRect = 0;
            isEll = 1;
            break;
        }
        }
        break;
    case WM_LBUTTONDOWN:
    {
        SetCapture(hWnd);
        GetClientRect(hWnd, &rc);
        ptClientUL.x = rc.left;
        ptClientUL.y = rc.top;
        ptClientLR.x = rc.right + 1;
        ptClientLR.y = rc.bottom + 1;
        ClientToScreen(hWnd, &ptClientUL);
        ClientToScreen(hWnd, &ptClientLR);
        SetRect(&rc, ptClientUL.x, ptClientUL.y, ptClientLR.x, ptClientLR.y);
        ClipCursor(&rc);
        ptsBegin = MAKEPOINTS(lParam);
        break;
    }

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON) {

            hdc = GetDC(hWnd);
            SetROP2(hdc, R2_NOTXORPEN);

            if (fPrevLine && isLine) {
                pen = CreatePen(PS_SOLID, 2, RGB(225, 0, 0));
                SelectObject(hdc, pen);
                MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
                LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
            }
            if (fPrevLine && isRect) {
                pen = CreatePen(PS_SOLID, 2, RGB(0, 225, 0));
                SelectObject(hdc, pen);
                Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsPrevEnd.x, ptsPrevEnd.y);
            }
            if (fPrevLine && isEll) {
                pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 225));
                SelectObject(hdc, pen);
                Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsPrevEnd.x, ptsPrevEnd.y);
            }

            ptsEnd = MAKEPOINTS(lParam);
            if (isLine)
            {
                MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
                LineTo(hdc, ptsEnd.x, ptsEnd.y);
            }
            if (isRect)
            {
                Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
            }
            if (isEll)
            {
                Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
            }

            fPrevLine = TRUE;
            ptsPrevEnd = ptsEnd;
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_LBUTTONUP:
        fPrevLine = FALSE;
        ClipCursor(NULL);
        ReleaseCapture();
        break;
    }
}

void lab5(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HANDLE& hTreadPaint, STARTUPINFO& tin, PROCESS_INFORMATION& pInfo, DWORD& exitCode) {
    switch (message)
    {
    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            MyEllipse NewEllipse;
            NewEllipse.hThread = CreateThread(NULL, 0, *ThreadBall, (LPVOID)hWnd, 0, NULL);
            massEllipse.push_back(NewEllipse);
        }
        break;
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case ID_PROCESSES_CREATEPROCESS:
            GetExitCodeProcess(pInfo.hProcess, &exitCode);
            if (exitCode != STILL_ACTIVE) CreateProcess(L"C:\\Windows\\notepad.exe", NULL,
                NULL, NULL, FALSE, 0, NULL, NULL, &tin, &pInfo);
            break;
        case ID_PROCESSES_DELETEPROCESS:
            GetExitCodeProcess(pInfo.hProcess, &exitCode);
            if (exitCode == STILL_ACTIVE) TerminateProcess(pInfo.hProcess, 0);
            else MessageBox(hWnd, L"Даний процес відсутній. Будь ласка, запустіть спочатку Ваш редактор!", L"", MB_OK);
            break;
        default:
            break;
        }
    }
    break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        for (int i = 0; i < massEllipse.size(); i++) {
            Ellipse(hdc, massEllipse[i].cx, massEllipse[i].cy, massEllipse[i].cx + R, massEllipse[i].cy + R);
        }
        EndPaint(hWnd, &ps);
    }
        break;
    default:
        break;
    }
}

void lab6(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    static TCHAR name[256] = _T("");
    static TCHAR lastOpen[256] = _T("");
    static TCHAR delName[256] = _T("");
    static TCHAR info[1024] = _T("");
    static TCHAR drives[1024] = _T("");
    static TCHAR curDir[256];
    static TCHAR newName[256];
    TCHAR* drive;
    HANDLE hFile;
    static OPENFILENAME file;
    std::ifstream in;
    static std::vector<std::string> v;
    std::vector<std::string>::iterator it;
    std::string st;
    int y;
    GetCurrentDirectory(256, curDir);
    file.lStructSize = sizeof(OPENFILENAME);
    file.hInstance = hInst;
    file.lpstrFile = name;
    file.nMaxFile = 256;
    file.lpstrInitialDir = _T(".\\");
    file.lpstrDefExt = _T("txt");

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_FILE_CREATE:
            file.lpstrTitle = L"Створіть файл";
            file.Flags = OFN_HIDEREADONLY;
            if (GetSaveFileName(&file))
            {
                HANDLE hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile != INVALID_HANDLE_VALUE)
                {
                    DWORD dwBytesWritten;
                    WriteFile(hFile, "NEW FILE!\n", 10, &dwBytesWritten, NULL);
                    CloseHandle(hFile);
                }
            }
            break;
        case ID_FILE_OPEN:
            if (!v.empty()) std::vector<std::string>().swap(v);
            file.lpstrTitle = L"Оберіть файл для відкриття";
            file.lpstrFilter = _T("Text\0*.txt");
            file.Flags = OFN_HIDEREADONLY;;
            if (!GetOpenFileName(&file))
                break;

            in.open(name);

            while (getline(in, st))
                v.push_back(st);

            in.close();
            _tcscpy_s(lastOpen, 256, name);
            InvalidateRect(hWnd, NULL, 1);
            break;
        case ID_FILE_SAVE:
            wsprintf(newName, L"%s\\%hs.txt", curDir, GenerateUniqueName(1).c_str());
            hFile = CreateFile(newName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);

            if (hFile != INVALID_HANDLE_VALUE)
            {
                DWORD dwBytesWritten;
                WriteFile(hFile, "SAVE FILE!\n", 11, &dwBytesWritten, NULL);
                for (it = v.begin(); it < v.end(); ++it)
                {
                    WriteFile(hFile, it->data(), it->length(), &dwBytesWritten, NULL);
                    WriteFile(hFile, "\n", 1, &dwBytesWritten, NULL);

                }
                CloseHandle(hFile);
            }
            break;
        case ID_FILE_COPY:
            _tcscpy_s(newName, 256, lastOpen);
            PathRemoveFileSpec(newName);
            wsprintf(newName, L"%s\\%hs.txt", newName, GenerateUniqueName(0).c_str());
            CopyFile(lastOpen, newName, 0);
            break;
        case ID_TYPESDELETING_TXT:
            wsprintf(delName, L"%s\\*.txt", curDir);
            if (!deleteAllFile(curDir, delName, 0))
                MessageBox(NULL, L"Невдалося видалити файли", L"Error", MB_ICONERROR | MB_OK);
            break;
        case ID_TYPESDELETING_DOCX:
            wsprintf(delName, L"%s\\*.docx", curDir);
            if (!deleteAllFile(curDir, delName, 0))
                MessageBox(NULL, L"Невдалося видалити файли", L"Error", MB_ICONERROR | MB_OK);
            break;
        case ID_TYPESDELETING_HIDDEN:
            wsprintf(delName, L"%s\\*.*", curDir);
            if (!deleteAllFile(curDir, delName, 1))
                MessageBox(NULL, L"Невдалося видалити файли", L"Error", MB_ICONERROR | MB_OK);
            break;
        case ID_FILE_INFO:
            file.lpstrFilter = L"All Files\0*.*\0";
            file.Flags = OFN_HIDEREADONLY;
            if (!GetOpenFileName(&file))
                break;
            hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile != INVALID_HANDLE_VALUE) {
                BY_HANDLE_FILE_INFORMATION fileInfo;
                if (GetFileInformationByHandle(hFile, &fileInfo)) {
                    TCHAR fileTime[20], fileDate[20], fileSize[20], attributes[10];

                    SYSTEMTIME stUTC, stLocal;
                    FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &stUTC);
                    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
                    wsprintf(fileTime, L"%02d:%02d:%02d", stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

                    wsprintf(fileDate, L"%02d/%02d/%04d", stLocal.wMonth, stLocal.wDay, stLocal.wYear);

                    wsprintf(fileSize, L"%I64u bytes", ((ULONGLONG)fileInfo.nFileSizeHigh << 32) | fileInfo.nFileSizeLow);

                    wsprintf(attributes, L"%c%c%c%c%c%c%c%c", (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) ? 'A' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) ? 'C' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 'D' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? 'H' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ? 'N' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? 'R' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) ? 'S' : '-',
                        (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) ? 'T' : '-');

                    wsprintf(info, L"File Name: %s\nFile Time: %s\nFile Date: %s\nFile Size: %s\nFile Attributes: %s",
                        name, fileTime, fileDate, fileSize, attributes);
                    MessageBox(hWnd, info, L"File Information", MB_OK);
                }
                CloseHandle(hFile);
            }
            break;
        case ID_FILE_MOVETOANOTHERLOGICDISK:
            GetLogicalDriveStrings(1024, drives);

            drive = drives;
            while (*drive)
            {

                TCHAR driveLetter = drive[0];
                TCHAR fileDriveLetter = name[0];
                if (driveLetter != fileDriveLetter)
                {

                    _tcscpy_s(newName, 256, drive);
                    break;
                }

                drive += _tcslen(drive) + 1;
            }

            wsprintf(newName, L"%s%s", newName, PathFindFileName(name));

            if (MoveFile(name, newName))
                MessageBox(NULL, newName, L"Info", MB_OK);
            else
                MessageBox(NULL, L"Неможливо перемістити", L"Error", MB_OK | MB_ICONERROR);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        for (y = 0, it = v.begin(); it < v.end(); ++it, y += 16)
            TextOutA(hdc, 0, y, it->data(), it->length());
        EndPaint(hWnd, &ps);

    }
    }
}