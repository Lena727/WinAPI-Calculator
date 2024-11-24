#include "MainWindow.h"
#include "Buttons.h"


static LPCWSTR CLASS_NAME = L"CalcWnd";
static WCHAR displayText[64] = { L'\0' };
static int cursor = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        rect.top = 10;
        rect.left = 10;
        rect.right -= 10;
        DrawTextW(hdc, displayText, (int)wcslen(displayText), &rect, DT_RIGHT | DT_VCENTER);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_COMMAND:
        Buttons_HandleCommand(hwnd, LOWORD(wParam), &cursor, displayText);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

BOOL MainWindow_RegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&wc);
}

HWND MainWindow_Create(HINSTANCE hInstance) {
    CONST INT WINX = 400, WINY = 600 - GetSystemMetrics(SM_CYCAPTION);
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Calculator",
        WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE),
        CW_USEDEFAULT, CW_USEDEFAULT, WINX, WINY,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd != NULL) {
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        int clientWidth = clientRect.right - clientRect.left;
        int clientHeight = clientRect.bottom - clientRect.top;

        Buttons_Create(hwnd, hInstance, clientWidth, clientHeight);
    }

    return hwnd;
}

int MainWindow_Run() {
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
    