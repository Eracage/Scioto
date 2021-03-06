#include <Window.h>
#include <string>
#include <OpenGL.h>
#include <Engine.h>
#include <Viewport.h>
#pragma comment(lib, "opengl32.lib")

namespace Scioto
{
	HWND Window::handle;
	HGLRC Window::OGLcontext;
	HDC Window::hdc;
	//float Window::SCALE, Window::BLACKBARH, Window::BLACKBARV;

	Window::Window(HINSTANCE instance,const char* windowName,int width,int height)
	{
	//Windowclass, defines template for windows
		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = wEventsProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = instance;
		wndClass.hIcon = NULL;
		wndClass.hCursor = NULL;
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = L"windowClass";
		wndClass.hIconSm = NULL;

		
		DWORD wStyle = 
			//WS_VISIBLE | 
			//WS_POPUP | 
			WS_OVERLAPPED |
			//WS_VSCROLL |
			WS_BORDER | 
			WS_SYSMENU | 
			WS_CAPTION | 
			WS_MINIMIZEBOX |
			WS_MAXIMIZEBOX |
			//WS_THICKFRAME |
			NULL;
		
		RECT windowRect;
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = width;
		windowRect.bottom = height;

		AdjustWindowRect(&windowRect,wStyle,false);

		//register window class
		if(!RegisterClassEx(&wndClass))
		{
			//FAIL
		}

		//Creates window and return handle to it (a way to access the windows attributes)
		handle = CreateWindowA("windowClass", windowName, wStyle, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, instance, NULL);

		if (handle == NULL)
		{
			//0.o
		}

		ShowWindow(handle, SW_SHOWNORMAL);
		UpdateWindow(handle);

		//pixel format description, only point worth of notice is if its 32 or 24 bit (alpha or no alpha)
				PIXELFORMATDESCRIPTOR pixelFormatDesc = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			24, 0, 0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
	
		//Device Contex handle
		hdc = GetDC(handle); // Gets the display context

		if(hdc == NULL) {

			//0.o
		}

		int pixelFormat = ChoosePixelFormat(hdc, &pixelFormatDesc); // Chooses the pixel format

		if(pixelFormat == 0) {

			//0.o
		}

		// Sets the pixel format
		if(SetPixelFormat(hdc, pixelFormat, &pixelFormatDesc) == 0) {

			//return 0;
		}

		HGLRC hglrc = wglCreateContext(hdc); // Creates the rendering context

		if(hglrc == NULL) {

			//0.o
		}

		// Attaches the rendering context
		if(wglMakeCurrent(hdc, hglrc) == 0) {

			//return 0;
		}
	
		LoadOpenGLFunctions(); // Loads OpenGL 2.1 functions
		MSG msg ={};
		Engine* engine = new Engine(width, height);
		// Main message loop:
		while(msg.message != WM_QUIT)
		{
		
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
			else // We've processed all pending Win32 messages, and can now do a rendering update.
			{
				engine->Update();
				engine->Draw();
				SwapBuffers(Window::hdc); // Swaps display buffers
			}
		}
	}

	Window::~Window(void)
	{
	}


	LRESULT CALLBACK Window::wEventsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 1;
	}
}