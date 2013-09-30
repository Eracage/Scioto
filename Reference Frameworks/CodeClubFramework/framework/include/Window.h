/**
 * @file Window.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

namespace glframework
{
	class Window
	{
	public:
		
		Window(HWND handle);

		Window(const Window& window);

		~Window();

		int width() const;

		int height() const;

		void createContext();

		bool processMessages() const;
		
		void swapBuffers() const;

	private:

		HWND _handle;
		HDC _deviceContext;
		HGLRC _renderingContext;

		int _width;
		int _height;

		PIXELFORMATDESCRIPTOR pixelFormatDescriptor() const;
		
		void initialize();
		void destroy();
		void getDeviceContext();
		int choosePixelFormat(PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const;
		void setPixelFormat(PIXELFORMATDESCRIPTOR& pixelFormatDescriptor, const int pixelFormat) const;
		void createRenderingContext();
		void attachRenderingContext();
		void initializeGLEW() const;
		void destroyContext();
		void destroyWindow() const;
		void setPointer() const;
		void getWindowSize();
		bool setRenderingContext(HGLRC renderingContext);
		void detachRenderingContext();
		void destroyRenderingContext();
	};
}

#endif