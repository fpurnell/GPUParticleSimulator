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

static TCHAR szWindowClass[] = _T("Particle Simulator Handler");
static TCHAR szTitle[] = _T("Particle Simulator Handler");
HINSTANCE hInst;


BOOL InitApp(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumChildProc(HWND, LPARAM);
BOOL InitInst(HINSTANCE, int);
BOOL FuncMoveWindow(HWND[], HWND );


int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
  InitApp(hInstance);
  InitInst(hInstance, nCmdShow);




  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}
BOOL InitApp(HINSTANCE hInstance)
{
  WNDCLASSEX mwin;
  {
    mwin.cbSize = sizeof(WNDCLASSEX);
    mwin.style = CS_HREDRAW | CS_VREDRAW;
    mwin.lpfnWndProc = WndProc;
    mwin.cbClsExtra = 0;
    mwin.cbWndExtra = 0;
    mwin.hInstance = hInstance;
    mwin.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    mwin.hCursor = LoadCursor(NULL, IDC_ARROW);
    mwin.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    mwin.lpszMenuName = TEXT("MainMenu");
    mwin.lpszClassName = TEXT("MainWindowClass");
    mwin.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
  }
  WNDCLASSEX rwin;
  {
    rwin.cbSize = sizeof(WNDCLASSEX);
    rwin.style = CS_HREDRAW | CS_VREDRAW;
    rwin.lpfnWndProc = WndProc;
    rwin.cbClsExtra = 0;
    rwin.cbWndExtra = 0;
    rwin.hInstance = hInstance;
    rwin.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    rwin.hCursor = LoadCursor(NULL, IDC_ARROW);
    rwin.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    rwin.lpszMenuName = TEXT("ResultsMenu");
    rwin.lpszClassName = TEXT("ResultsWindowClass");
    rwin.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
  }
  WNDCLASSEX inchild;
  {
    inchild.lpszClassName = TEXT("InnerChildClass");
    inchild.style = MDIS_ALLCHILDSTYLES;
  }
  return (RegisterClassEx(&mwin) && RegisterClassEx(&rwin) && RegisterClassEx(&inchild));
}
BOOL InitInst(HINSTANCE hInstance, int nCmdShow)
{
  /*
  Child Windows used:
  STATIC                DROPDOWN
  Type of Computing     Single/Multi/GPU
  STATIC                TEXTBOX (disabled)
  Number of Cores       2

  
  
  




  */
  HMENU MainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_DESKTOPAPPLICATION));
  HMENU ResultsMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
  //RECT rc;


  //ClearType
  /*SystemParametersInfo(SPI_SETFONTSMOOTHING,
  TRUE,
  0,
  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
  SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE,
  0,
  (PVOID)FE_FONTSMOOTHINGCLEARTYPE,
  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);*/

  HWND mainW = CreateWindow(
    TEXT("MainWindowClass"), TEXT("Partcle Simulation Handler"),
    WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT, 1000 + 5, 325,
    NULL,    MainMenu,    hInstance,    NULL
  );
  if (!mainW)
  {
    MessageBox(NULL,
      _T("Create Main Window Failed!"),
      _T("Particle Simulation Handler"),
      NULL);
    return 1;
  }

  HWND resultsW = CreateWindow(
    TEXT("ResultsWindowClass"),    TEXT(""),
    WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT,    1000 + 5, 325,
    NULL,    ResultsMenu,    hInstance,    NULL
  );
  if (!resultsW)
  {
    MessageBox(NULL,
      _T("Create Results Window Failed!"),
      _T("Particle Simulation Handler"),
      NULL);
    return 1;
  }

  HWND textW1 = CreateWindow(
    WC_STATIC, TEXT("textbox1"), SS_SIMPLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    mainW, NULL, NULL, NULL
  );
  HWND textW2 = CreateWindow(
    WC_STATIC, TEXT("textbox2"), NULL,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    mainW, NULL, NULL, NULL
  );
  HWND textW3 = CreateWindow(
    WC_STATIC, TEXT("textbox3"), NULL,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    mainW, NULL, NULL, NULL
  );
  HWND textW4 = CreateWindow(
    WC_STATIC, TEXT("textbox4"), NULL,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    mainW, NULL, NULL, NULL
  );
  HWND ddW1 = CreateWindow(
    WC_COMBOBOX,    TEXT("dropdown1"),    CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    mainW, NULL, NULL, NULL);
  HWND childExW1 = CreateWindow(
    TEXT(""),
    TEXT(""),
    WS_CHILD | WS_BORDER,
    0, 0, 0, 0,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  
    //3
    //4
  TCHAR sz[160];
  LoadString(hInst, IDS_COMPUTE_STRING_2, sz, sizeof(sz) / sizeof(TCHAR));
  SendMessage(
    ddW1,
    (UINT)CB_ADDSTRING, 
    (WPARAM)0, 
    (LPARAM)sz);
  LoadString(hInst, IDS_COMPUTE_STRING_3, sz, sizeof(sz) / sizeof(TCHAR));
  SendMessage(
    ddW1,
    (UINT)CB_ADDSTRING,
    (WPARAM)1,
    (LPARAM)sz);
  LoadString(hInst, IDS_COMPUTE_STRING_4, sz, sizeof(sz) / sizeof(TCHAR));
  SendMessage(
    ddW1,
    (UINT)CB_ADDSTRING,
    (WPARAM)2,
    (LPARAM)sz);
  SendMessage(ddW1, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

  SetParent(textW1, mainW);
  SetParent(textW2, mainW);
  SetParent(textW3, mainW);
  SetParent(textW4, mainW);
  SetParent(ddW1, mainW);
  
  UpdateWindow(ddW1);
  UpdateWindow(textW1);
  UpdateWindow(textW2);
  UpdateWindow(textW3);
  UpdateWindow(textW4);
  UpdateWindow(mainW);
  UpdateWindow(childExW1);

  
  HWND children[] = { textW1, textW2, textW3, textW4, ddW1 };
  FuncMoveWindow(children, mainW);

  ShowWindow(mainW, nCmdShow);
  ShowWindow(ddW1, nCmdShow);
  ShowWindow(textW1, nCmdShow);
  ShowWindow(textW2, nCmdShow);
  ShowWindow(textW3, nCmdShow);
  ShowWindow(textW4, nCmdShow);
  ShowWindow(childExW1, nCmdShow);
  
  return true;

}
LRESULT CALLBACK WndProc(HWND mainW, UINT message, WPARAM wParam, LPARAM lParam)
{

  PAINTSTRUCT ps;
  HDC hdc;
  RECT rcClient;


  switch (message)
  {
  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case IDM_EXIT:
      PostQuitMessage(0);
      break;
    case ID_FILE_LOADDEFAULT:
      break;
    case ID_FILE_LOAD:
      break;
    case ID_FILE_SAVE:
      break;
    case IDM_ABOUT:
      //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), mainW, TEXT("About"));
      break;
    default:
      return DefWindowProc(mainW, message, wParam, lParam);
    }
  case WM_PAINT:
    hdc = BeginPaint(mainW, &ps);
    EndPaint(mainW, &ps);
    break;
  case WM_CLOSE:
    PostQuitMessage(0);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_SIZE:
    GetClientRect(mainW, &rcClient);
    EnumChildWindows(mainW, EnumChildProc, (LPARAM)&rcClient);
    return 0;
    break;
  default:
    return DefWindowProc(mainW, message, wParam, lParam);
    break;
  }

  return 0;
}
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
  LPRECT rcParent;
  int idChild;
  int i = 0;
  idChild = GetWindowLong(hwndChild, GWL_ID);

  switch (idChild)
  {
  case 0:
    i = 0;
    break;
  case 1:
    i = 1;
    break;
  case 2:
    i = 2;
    break;
  default:
    break;
  }
  rcParent = (LPRECT)lParam;
  idChild = GetWindowLong(hwndChild, GWL_ID);

  

  return TRUE;
}
BOOL FuncMoveWindow(HWND children[], HWND mainW)
{
  RECT rcParent;
  LPRECT rcClient = &rcParent;
  GetClientRect(mainW, rcClient);
  HWND textW1 = children[0];
  HWND textW2 = children[1];
  HWND textW3 = children[2];
  HWND textW4 = children[3];
  HWND ddW1 = children[4];
  MoveWindow(textW1,
    (rcClient->right / 4) * 0,
    rcClient->top + ROW1,
    rcClient->right / 4,
    ROW_HEIGHT,
    FALSE);
  MoveWindow(textW2,
    (rcClient->right / 4) * 0,
    rcClient->top + ROW2,
    rcClient->right / 4,
    ROW_HEIGHT,
    FALSE);
  MoveWindow(textW3,
    (rcClient->right / 4) * 2,
    rcClient->top + ROW1,
    rcClient->right / 4,
    ROW_HEIGHT,
    FALSE);
  MoveWindow(textW4,
    (rcClient->right / 4) * 2,
    rcClient->top + ROW2,
    rcClient->right / 4,
    ROW_HEIGHT,
    FALSE);
  MoveWindow(ddW1,
    (rcClient->right / 4) * 1,
    rcClient->top + ROW1,
    rcClient->right / 4,
    ROW_HEIGHT,
    FALSE);
  return true;
}