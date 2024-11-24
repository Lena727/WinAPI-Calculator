#include "Buttons.h"
#include "eval.h"
#include <wchar.h>

void Buttons_Create(HWND hWnd, HINSTANCE hInstance, int clientWidth, int clientHeight) {
    CONST INT ROW = 5, COL = 4;
    const WCHAR ButtonNameTable[20] = {
        L"C<%/"
        L"789*"
        L"456-"
        L"123+"
        L"0 .=" 
    };
    const int ButtonIndexTable[20] = {
        BUTTON_CLEAR, BUTTON_ERASE, BUTTON_MODULE, BUTTON_DIVIDE,
        BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_MULTIPLY,
        BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_MINUS,
        BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_PLUS,
        BUTTON_0, BUTTON_NONE, BUTTON_DOT, BUTTON_EQUAL
    };
    INT BUTTONX = clientWidth / COL, BUTTONY = (clientHeight - 145) / ROW;

    for (int y = 0; y < ROW; ++y) {
        for (int x = 0; x < COL; ++x) {
            int index = y * COL + x;
            WCHAR name[2] = { ButtonNameTable[index], L'\0' };
            switch (ButtonIndexTable[index])
            {
            case BUTTON_NONE:
                break;
            case BUTTON_0:
                CreateWindowExW(
                    0,
                    L"BUTTON",
                    name,
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    BUTTONX * x, 150 + BUTTONY * y, BUTTONX*2, BUTTONY,
                    hWnd,
                    (HMENU)ButtonIndexTable[index],
                    hInstance,
                    NULL
                );
                break;
            default:
                CreateWindowExW(
                    0,
                    L"BUTTON",
                    name,
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    BUTTONX * x, 150 + BUTTONY * y, BUTTONX, BUTTONY,
                    hWnd,
                    (HMENU)ButtonIndexTable[index],
                    hInstance,
                    NULL
                );
                break;
            }
        }
    }
}

void Buttons_HandleCommand(HWND hwnd, int buttonId, int* cursor, WCHAR* displayText) {
    if (BUTTON_0 <= buttonId && buttonId <= BUTTON_9) {
        if (*cursor < 64) {
            displayText[(*cursor)++] = L'0' + (buttonId - BUTTON_0);
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    else if (BUTTON_PLUS <= buttonId && buttonId <= BUTTON_MODULE) {
        if (buttonId == BUTTON_MINUS) {
            if (*cursor == 0 || wcschr(L"+*/%(", displayText[*cursor - 1])) {
                displayText[(*cursor)++] = '-';
                InvalidateRect(hwnd, NULL, TRUE);
            }
            else if (*cursor > 0 && iswdigit(displayText[*cursor - 1])) {
                displayText[(*cursor)++] = '-';
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
        if (*cursor > 0 && *cursor < 64) {
            WCHAR lastChar = displayText[*cursor - 1];

            if (wcschr(L"+-*/%.", lastChar)) return;

            displayText[(*cursor)++] = L"+-*/%"[buttonId - BUTTON_PLUS];
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    else if (buttonId == BUTTON_ERASE) {
        if (*cursor > 0) {
            displayText[--(*cursor)] = L'\0';
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    else if (buttonId == BUTTON_CLEAR) {
        ZeroMemory(displayText, sizeof(WCHAR) * 64);
        *cursor = 0;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    else if (buttonId == BUTTON_EQUAL) {
        Token* tokens = TokenizeW(displayText);
        if (!tokens) {
            ZeroMemory(displayText, sizeof(WCHAR) * 64);
            *cursor = 0;
            MessageBoxW(0, L"Expression invalid", L"Error", MB_ICONERROR);
            InvalidateRect(hwnd, NULL, TRUE);
            return;
        }
        Number result = eval(tokens);
        FreeToken(tokens);
        ZeroMemory(displayText, sizeof(WCHAR) * 64);
        *cursor = swprintf(displayText, 64, L"%.10g", result);

        InvalidateRect(hwnd, NULL, TRUE);
    }
    else if (buttonId == BUTTON_DOT) {
        if (*cursor > 0) {
            WCHAR lastChar = displayText[*cursor - 1];

            int i = *cursor - 1;
            while (i >= 0 && iswdigit(displayText[i])) i--;
            if (i >= 0 && displayText[i] == '.') return;

            if (!iswdigit(lastChar)) {
                displayText[(*cursor)++] = '0';
            }
        }
        else {
            displayText[(*cursor)++] = '0';
        }
        displayText[(*cursor)++] = '.';
        InvalidateRect(hwnd, NULL, TRUE);
    }
}