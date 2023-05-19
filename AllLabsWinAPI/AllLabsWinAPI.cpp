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
void lab2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void lab4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
       WS_OVERLAPPEDWINDOW | WS_VSCROLL | SWP_NOZORDER | SWP_NOACTIVATE | WS_HSCROLL,    // стиль вікна
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
    int screenX = 800;
    int screenY = 500;

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
        break;
    case 6:
        break;
    case 7:
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
                screenY = 500;
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
            case ID_LABS_5:
                labNumber = 5;
                InvalidateRect(hWnd, NULL, TRUE);
                break;   
            case ID_LABS_6:
                labNumber = 6;
                InvalidateRect(hWnd, NULL, TRUE);
                break;   
            case ID_LABS_7:
                labNumber = 7;
                InvalidateRect(hWnd, NULL, TRUE);
                break;   
            case ID_LABS_8:
                labNumber = 8;
                InvalidateRect(hWnd, NULL, TRUE);
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
           
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