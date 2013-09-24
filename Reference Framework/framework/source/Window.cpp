/**
 * @file Window.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Window.h>

#include <cassert>
#include <GL/glew.h>

using namespace glframework;

Window::Window(HWND handle)
	: _handle(handle),
	  _deviceContext(NULL),
	  _renderingContext(NULL),
	  _width(0),
	  _height(0)
{
	initialize();
}

Window::Window(const Window& window)
	: _handle(window._handle),
	  _deviceContext(window._deviceContext),
	  _renderingContext(window._renderingContext)
{
	initialize();
}

Window::~Window()
{
	destroy();
}


// Public

int Window::width() const
{
	return _width;
}

int Window::height() const
{
	return _height;
}

void Window::createContext()
{
	getDeviceContext();
	PIXELFORMATDESCRIPTOR pixelFormatDesc = pixelFormatDescriptor();

	int pixelFormat = choosePixelFormat(pixelFormatDesc);
	setPixelFormat(pixelFormatDesc, pixelFormat);

	createRenderingContext();
	attachRenderingContext();

	initializeGLEW();
}

bool Window::processMessages() const
{
	MSG message;

	while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE) == TRUE)
	{
		DispatchMessage(&message);

		if(message.message == WM_CLOSE)
			return false;
	}

	return true;
}

void Window::swapBuffers() const
{
	SwapBuffers(_deviceContext);
}


// Private

PIXELFORMATDESCRIPTOR Window::pixelFormatDescriptor() const
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	return pixelFormatDescriptor;
}

void Window::initialize()
{
	setPointer();
	getWindowSize();
}

void Window::destroy()
{
	destroyContext();
	destroyWindow();
}

void Window::getDeviceContext()
{
	_deviceContext = GetDC(_handle);
	assert(_deviceContext != NULL);
}

int Window::choosePixelFormat(PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const
{
	int pixelFormat = ChoosePixelFormat(_deviceContext, &pixelFormatDescriptor);
	assert(pixelFormat != 0);

	return pixelFormat;
}

void Window::setPixelFormat(PIXELFORMATDESCRIPTOR& pixelFormatDescriptor, const int format) const
{
	BOOL result = SetPixelFormat(_deviceContext, format, &pixelFormatDescriptor);
	assert(result != FALSE);
}

void Window::createRenderingContext()
{
	_renderingContext = wglCreateContext(_deviceContext);
	assert(_renderingContext != NULL);
}

void Window::attachRenderingContext()
{
	bool result = setRenderingContext(_renderingContext);
	assert(result);
}

void Window::initializeGLEW() const
{
	GLenum result = glewInit();
	assert(result == GLEW_OK);
}

void Window::destroyContext()
{
	detachRenderingContext();
	destroyRenderingContext();
}

void Window::destroyWindow() const
{
	BOOL result = DestroyWindow(_handle);
	assert(result != FALSE);
}

void Window::setPointer() const
{
	SetLastError(0);
	SetWindowLongPtr(_handle, GWLP_USERDATA, (LONG)this);

	DWORD error = GetLastError();
	assert(error == 0);
}

void Window::getWindowSize()
{
	RECT windowRectangle;

	BOOL result = GetClientRect(_handle, &windowRectangle);
	assert(result != FALSE);

	_width = windowRectangle.right - windowRectangle.left;
	_height = windowRectangle.bottom - windowRectangle.top;
}

bool Window::setRenderingContext(HGLRC renderingContext)
{
	BOOL result = wglMakeCurrent(_deviceContext, renderingContext);
	return result == TRUE;
}

void Window::detachRenderingContext()
{
	bool result = setRenderingContext(NULL);
	assert(result);
}

void Window::destroyRenderingContext()
{
	BOOL result = wglDeleteContext(_renderingContext);
	assert(result != FALSE);
}