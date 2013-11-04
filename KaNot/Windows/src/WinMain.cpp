#include <Win32toAndroid.h>
#include <Window.h>
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	Scioto::Window * window = new Scioto::Window(hInstance,"MyWindow",800,800);
	return 0;
}