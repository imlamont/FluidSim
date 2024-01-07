#pragma once

#include "resource.h"
#include <Windows.h>
#include <GL/glew.h>
#include "Fluid.h"
#include <EZGL/ShaderProgram.h>
#include <EZGL/Camera.h>

#define MAX_LOADSTRING 100
#define TICK_TIMER 0

#define MAINWINDOW_WIDTH 750
#define MAINWINDOW_HEIGHT 600
class MainWindow
{
private:
	static HINSTANCE hInst;                                // current instance
	static WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	static WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	HWND hWnd;
	HGLRC context;

	Fluid fluid;
	EZGL::ShaderProgram prog;
	EZGL::Camera cam;

	unsigned int width;
	unsigned int height;

	void initalizeWindow(int nCmdShow);
	ATOM registerClass();
	void initalizeGL();
public:
	MainWindow(HINSTANCE hInstance, int nCmdShow);

	static void setCurrentHInst(HINSTANCE hInstance);
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

