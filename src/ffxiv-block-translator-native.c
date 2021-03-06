// ffxiv-block-translator-native.cpp : Defines the entry point for the application.
//


#include "ffxiv-block-translator-native.h"
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "translate.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWndInput;                                 // the input text box
HWND hWndOutput;                                // the output text box
HWND hWndButtonTranslate;                       // the translate button
HWND hWndButtonClear;                           // the clear button


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FFXIVBLOCKTRANSLATORNATIVE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FFXIVBLOCKTRANSLATORNATIVE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FFXIVBLOCKTRANSLATORNATIVE));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FFXIVBLOCKTRANSLATORNATIVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 
      CW_USEDEFAULT, 0, 480, 340, NULL, NULL, hInstance, NULL);

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
//  PURPOSE:  Processes messages for the main window.
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
    case WM_CREATE:
    {
        // create input box
        hWndInput = CreateWindowEx(
            WS_EX_WINDOWEDGE,
            TEXT("EDIT"),
            NULL,
            WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY,
            30,
            20,
            200,
            200,
            hWnd,
            (HMENU)IDC_INPUT_BOX,
            NULL,
            NULL);
        
        // create output box
        hWndOutput = CreateWindowEx(
            WS_EX_WINDOWEDGE,
            TEXT("EDIT"),   // predefined class; unicode assumed
            NULL,   // text
            WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY, // styles
            240,     // x
            20,     // y
            200,    // width
            200,    // height
            hWnd,   // parent window
            (HMENU)IDC_OUTPUT_BOX,  // no menu
            NULL,
            NULL);  // pointer not needed

        // hides the scroll bar from the input box
        ShowScrollBar(hWndInput, SB_VERT, FALSE);
        // hides scroll bar from the output box
        ShowScrollBar(hWndOutput, SB_VERT, FALSE);

        // BUTTONS

        // translate button
        HWND hwndButtonTranslate = CreateWindowEx(
            WS_EX_WINDOWEDGE,
            TEXT("BUTTON"),  // Predefined class; Unicode assumed 
            TEXT("Translate"),      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            230,         // x position 
            230,         // y position 
            100,        // Button width
            35,        // Button height
            hWnd,     // Parent window
            (HMENU)IDC_OPBUTTON_TRANSLATE,       // No menu.
            NULL,
            NULL);      // Pointer not needed.

        HWND hwndButtonClear = CreateWindowEx(
            WS_EX_WINDOWEDGE,
            TEXT("BUTTON"),  // Predefined class; Unicode assumed 
            TEXT("CLEAR"),      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            340,         // x position 
            230,         // y position 
            100,        // Button width
            35,        // Button height
            hWnd,     // Parent window
            (HMENU)IDC_OPBUTTON_CLEAR,       // No menu.
            NULL,
            NULL);      // Pointer not needed.

        if (!hWnd)
            MessageBox(NULL, TEXT("ListBox Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDC_OPBUTTON_TRANSLATE:
            {
                wchar_t input[1024];
                GetWindowText(hWndInput, input, 1024);
                wchar_t *translation = translate(input);
                SetWindowTextW(GetDlgItem(hWnd, IDC_OUTPUT_BOX), (LPCWSTR)translation);
                free(translation);
                break;
            }
            case IDC_OPBUTTON_CLEAR:
                SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT_BOX), TEXT(""));
                SetWindowText(GetDlgItem(hWnd, IDC_INPUT_BOX), TEXT(""));
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
    case WM_DESTROY:
        PostQuitMessage(0);
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

