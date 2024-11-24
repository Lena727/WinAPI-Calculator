#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>

BOOL MainWindow_RegisterClass(HINSTANCE hInstance);
HWND MainWindow_Create(HINSTANCE hInstance);
int MainWindow_Run();

#endif // MAINWINDOW_H