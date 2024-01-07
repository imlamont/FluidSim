#include "MainWindow.h"
#include <glm/glm.hpp>

HINSTANCE MainWindow::hInst = NULL;
WCHAR MainWindow::szTitle[MAX_LOADSTRING];
WCHAR MainWindow::szWindowClass[MAX_LOADSTRING];

MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
: hWnd(NULL), context(NULL), fluid(), prog(), cam(glm::vec3(0.f,0.f,2.f), glm::vec3(0.f,0.f,-1.f)),
width(MAINWINDOW_WIDTH), height(MAINWINDOW_HEIGHT) {
    setCurrentHInst(hInstance);
    initalizeWindow(nCmdShow);
    initalizeGL();
    
    prog.create("./vert.glsl", "./frag.glsl");
    fluid.intialize();
    prog.setModelMatrix(glm::mat4(glm::vec4(1, 0, 0, 0),
                                  glm::vec4(0, 1, 0, 0),
                                  glm::vec4(0, 0, 1, 0),
                                  glm::vec4(0, 0, 0, 1)));
}

void MainWindow::initalizeWindow(int nCmdShow) {
    // Initialize global strings
    LoadStringW(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInst, IDC_FLUIDSIM, szWindowClass, MAX_LOADSTRING);

    this->registerClass();

    this->hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInst, nullptr);
    SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    if (!hWnd)
    {
        MessageBox(nullptr, L"Window creation failed", L"Error", MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
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
    MainWindow* thisWindow = (MainWindow*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);

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
    case WM_PAINT:
    {
        glViewport(0,0,thisWindow->width,thisWindow->height);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        thisWindow->fluid.draw(&(thisWindow->prog), &(thisWindow->cam));

        /*glBegin(GL_TRIANGLES);

        glVertex4f(0, 1, 1, 1);
        glVertex4f(-0.866025, -0.5, 1, 1);
        glVertex4f(0.866025, -0.5, 1, 1);

        glEnd();*/

        SwapBuffers(GetDC(hWnd));
        ValidateRect(thisWindow->hWnd, NULL);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER:
        switch (wParam) 
        {
        case TICK_TIMER:
        {
            thisWindow->fluid.tick();
            RedrawWindow(thisWindow->hWnd, NULL, NULL, NULL);
        }
            break;
        }
        break;
    case WM_SIZE:
    {
        unsigned int width = LOWORD(lParam);
        unsigned int height = HIWORD(lParam);
        thisWindow->width = width;
        thisWindow->height = height;
        break;
    }
    case WM_QUIT:
    {
        wglMakeCurrent(NULL, NULL);
        PostQuitMessage(0);
    }
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

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        const GLubyte* str = glewGetErrorString(err);
        MessageBox(nullptr, (LPCWSTR)str, L"Error", MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

