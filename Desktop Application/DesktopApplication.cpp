// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <tchar.h>
#include <string.h>
#include "resource.h"
#include "targetver.h"
#include "stdafx.h"
#include "definitions.h"
#include <CommCtrl.h>

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
  HMENU mainMenu;
  mainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDI_DESKTOPAPPLICATION));

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



  //ClearType
  /*SystemParametersInfo(SPI_SETFONTSMOOTHING,
    TRUE,
    0,
    SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
  SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE,
    0,
    (PVOID)FE_FONTSMOOTHINGCLEARTYPE,
    SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);*/

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

  HWND mainW = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT,
    1000 + 5, 325,
    NULL,
    mainMenu,
    hInstance,
    NULL
  );


  if (!mainW)
  {
    MessageBox(NULL,
      _T("Call to CreateWindow failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }

  HWND resultsW = CreateWindow(
    TEXT(""),
    TEXT(""),
    WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT,
    1000 + 5, 325,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  HWND headerW = CreateWindow(
    WC_STATIC,
    TEXT(""), LEFT_COLUMN, HEADER_ROW,
    50, 50,
    (int) mainW, NULL, NULL, NULL, NULL
  );
  HWND ddW1 = CreateWindow(
    WC_COMBOBOX,
    TEXT(""), RIGHT_COLUMN, ROW3,
    50, 23,
    (int) mainW, NULL, NULL, NULL, NULL);
  TCHAR compStrings[3][20] = { TEXT("Single-Core CPU"), TEXT("Multi-Core CPU"), TEXT("GPU") };
  TCHAR compCombo[16];
  memset(&compCombo, 0, sizeof(compCombo));
  for (int i = 0; i < 3; i++)
  {
    wcscpy_s(compCombo, sizeof(compCombo) / sizeof(TCHAR), (TCHAR*)compStrings[i]);
    SendMessage(ddW1, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)compCombo);
  }
  SendMessage(ddW1, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

  // The parameters to ShowWindow explained:
  // mainW: the value returned from CreateWindow
  // nCmdShow: the fourth parameter from WinMain
  ShowWindow(mainW,
    nCmdShow);
  ShowWindow(ddW1, nCmdShow);
  ShowWindow(headerW, nCmdShow);
  UpdateWindow(ddW1);
  UpdateWindow(headerW);
  UpdateWindow(mainW);

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
LRESULT CALLBACK WndProc(HWND mainW, UINT message, WPARAM wParam, LPARAM lParam)
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
    hdc = BeginPaint(mainW, &ps);
    //hdc = BeginPaint(headerW, &ps);
    //hdc = BeginPaint(ddW1, &ps);
    EndPaint(mainW, &ps);
    //EndPaint(headerW, &ps);
    //EndPaint(ddW1, &ps);
    break;
  case WM_CLOSE:
    PostQuitMessage(0);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(mainW, message, wParam, lParam);
    break;
  }

  return 0;
}
