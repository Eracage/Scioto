/**
 * @file WindowFactory.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include <Windows.h>
#include <Window.h>

namespace glframework
{
	class WindowFactory
	{
	public:

		WindowFactory();
		
		~WindowFactory();

		Window* create(const int width, const int height) const;

	private:

		static const WCHAR* WINDOW_CLASS_NAME;
		static const WCHAR* WINDOW_TITLE;

		HINSTANCE _instanceHandle;
		WNDCLASSEX _windowClass;

		WindowFactory(const WindowFactory& windowFactory);

		void initialize();
		void destroyWindowClass();
		HWND createWindow(const int width, const int height) const;
		void createWindowClass();
		void registerWindowClass();
		RECT createWindowRectangle(const int width, const int height, const DWORD style) const;
		void initializeInput(HWND windowHandle) const;

		static LRESULT CALLBACK processMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		static void processInput(const HRAWINPUT inputDataHandle);
		static void processMouseMovement(const LPARAM coords);
		static RAWINPUT* getInputData(const HRAWINPUT inputDataHandle);
		static Window* getWindowPointer(HWND windowHandle);
	};
}

#endif