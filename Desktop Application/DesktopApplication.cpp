// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <tchar.h>
#include <string.h>
#include "resource.h"
#include "targetver.h"
#include "stdafx.h"
#include "definitions.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("Particle Simulator Handler");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Particle Simulator Handler");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
  HICON icon, iconSmall;
  icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  iconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));

  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = icon;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = iconSmall;

  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL,
      _T("Call to RegisterClassEx failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }




  // Store instance handle in our global variable
  hInst = hInstance;

  // The parameters to CreateWindow explained:
  // szWindowClass: the name of the application
  // szTitle: the text that appears in the title bar
  // WS_OVERLAPPEDWINDOW: the type of window to create
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
  // 500, 100: initial size (width, length)
  // NULL: the parent of this window
  // NULL: this application does not have a menu bar
  // hInstance: the first parameter from WinMain
  // NULL: not used in this application
  HWND hWnd = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    1000 + 5, 325,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (!hWnd)
  {
    MessageBox(NULL,
      _T("Call to CreateWindow failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }

  // The parameters to ShowWindow explained:
  // hWnd: the value returned from CreateWindow
  // nCmdShow: the fourth parameter from WinMain
  ShowWindow(hWnd,
    nCmdShow);
  UpdateWindow(hWnd);

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  TCHAR head1[] = _T("Choose from the following options:");
  TCHAR comp10[] = _T("Computing Method");
  TCHAR comp110[] = _T("Single-Core CPU");
  TCHAR comp12[] = _T("Multi-Core CPU");
  TCHAR comp13[] = _T("GPU");
  TCHAR comp111[] = _T("Number of Threads");
  TCHAR boundary10[] = _T("Boundary Options");
  TCHAR boundary11[] = _T("");
  TCHAR boundary120[] = _T("Square");
  TCHAR boundary130[] = _T("Rectangle");
  TCHAR boundary140[] = _T("Circle");
  TCHAR boundary150[] = _T("Concentric Circle");
  TCHAR boundary121[] = _T("Side Length");
  TCHAR boundary131[] = _T("X Length");
  TCHAR boundary132[] = _T("Y Lengh");
  TCHAR boundary141[] = _T("Radius");
  TCHAR boundary151[] = _T("Outer Radius");
  TCHAR boundary152[] = _T("Inner Radius");
  TCHAR PLACEHOLDER[] = _T("PLACEHOLDER");

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    TextOut(hdc,
      LEFT_COLUMN, HEADER_ROW,
      head1, _tcslen(head1));
    TextOut(hdc,
      LEFT_COLUMN, ROW1,
      comp10, _tcslen(comp10));
    TextOut(hdc,
      LEFT_COLUMN, ROW2,
      comp110, _tcslen(comp110));
    TextOut(hdc,
      LEFT_COLUMN, ROW3,
      boundary10, _tcslen(boundary10));

    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}
