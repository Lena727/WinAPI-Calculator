#ifndef BUTTONS_H
#define BUTTONS_H

#include <windows.h>

#define BUTTON_NONE     0x100

#define BUTTON_0        0x1A0
#define BUTTON_1        0x1A1
#define BUTTON_2        0x1A2
#define BUTTON_3        0x1A3
#define BUTTON_4        0x1A4
#define BUTTON_5        0x1A5
#define BUTTON_6        0x1A6
#define BUTTON_7        0x1A7
#define BUTTON_8        0x1A8
#define BUTTON_9        0x1A9

#define BUTTON_PLUS     0x1B0
#define BUTTON_MINUS    0x1B1
#define BUTTON_MULTIPLY 0x1B2
#define BUTTON_DIVIDE   0x1B3
#define BUTTON_MODULE   0x1B4

#define BUTTON_EQUAL    0x1C0
#define BUTTON_ERASE    0x1C1
#define BUTTON_CLEAR    0x1C2
#define BUTTON_DOT      0x1C3

void Buttons_Create(HWND hWnd, HINSTANCE hInstance, int clientWidth, int clientHeight);
void Buttons_HandleCommand(HWND hwnd, int buttonId, int* cursor, WCHAR* displayText);

#endif // BUTTONS_H