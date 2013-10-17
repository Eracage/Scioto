#pragma once
#include <Windows.h>
class Window
{
public:
	Window(HINSTANCE instance,const char* windowName,int width,int height);
	~Window(void);

	static HWND handle;
	static HGLRC OGLcontext;
	static HDC hdc;
	static float SCALE, BLACKBARH, BLACKBARV;

	static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	static void FIXASPECTRATIO(float desiredWidth,float desiredHeight,float width,float height);

private:

	
};

