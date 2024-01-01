#include "MainWindow.h"
#include <glm/glm.hpp>

HINSTANCE MainWindow::hInst = NULL;
WCHAR MainWindow::szTitle[MAX_LOADSTRING];
WCHAR MainWindow::szWindowClass[MAX_LOADSTRING];

MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
: hWnd(NULL), context(NULL), fluid(), prog(), cam(glm::vec3(0.f,0.f,10.f), glm::vec3(0.f,0.f,-1.f)) {
    setCurrentHInst(hInstance);
    initalizeWindow(nCmdShow);
    initalizeGL();

    prog.create("c:/users/imlam/source/repos/fluidsim/vert.glsl","c:/users/imlam/source/repos/fluidsim/frag.glsl");
    fluid.intialize();
}

void MainWindow::initalizeWindow(int nCmdShow) {
    // Initialize global strings
    LoadStringW(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInst, IDC_FLUIDSIM, szWindowClass, MAX_LOADSTRING);

    this->registerClass();

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
    SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    if (!hWnd)
    {
        MessageBox(nullptr, L"Window creation failed", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    SetTimer(hWnd, TICK_TIMER, 17, (TIMERPROC)NULL);

    ShowWindow(hWnd, nCmdShow);
    //UpdateWindow(hWnd);
}

ATOM MainWindow::registerClass() {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FLUIDSIM));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FLUIDSIM);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hWnd, &ps);
    //    // TODO: Add any drawing code that uses hdc here...
    //    EndPaint(hWnd, &ps);
    //}
    //break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER:
        switch (wParam) 
        {
        case TICK_TIMER:
        {
            MainWindow* thisWindow = (MainWindow*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
            thisWindow->fluid.tick();
            thisWindow->fluid.draw(&(thisWindow->prog), &(thisWindow->cam));
        }
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void MainWindow::setCurrentHInst(HINSTANCE hInstance) {
    hInst = hInstance;
}

void MainWindow::initalizeGL() {
    PIXELFORMATDESCRIPTOR pdf = {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                32,
                0,0,0,0,0,0,
                0,
                0,
                0,
                0,0,0,0,
                24,
                8,
                0,
                PFD_MAIN_PLANE,
                0,
                0,0,0
    };

    HDC ourHDC = GetDC(hWnd);

    int windowsChosenPixFormat = ChoosePixelFormat(ourHDC, &pdf); // if return 0 theres an issue
    SetPixelFormat(ourHDC, windowsChosenPixFormat, &pdf);

    context = wglCreateContext(ourHDC);
    wglMakeCurrent(ourHDC, context);

    glewInit(); // should check for errors

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

