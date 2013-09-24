/**
 * @file WindowFactory.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <WindowFactory.h>
#include <cassert>

#include <Input.h>

using namespace glframework;

WindowFactory::WindowFactory()
	: _instanceHandle(NULL)
{
	initialize();
}
		
WindowFactory::~WindowFactory()
{
	destroyWindowClass();
}


// Public

Window* WindowFactory::create(const int width, const int height) const
{
	HWND windowHandle = createWindow(width, height);
	ShowWindow(windowHandle, SW_SHOWNORMAL);

	Window* window = new Window(windowHandle);
	window->createContext();

	return window;
}


// Private

const WCHAR* WindowFactory::WINDOW_CLASS_NAME = L"opengl-framework";
const WCHAR* WindowFactory::WINDOW_TITLE = L"OpenGL Framework";

void WindowFactory::initialize()
{
	_instanceHandle = GetModuleHandle(NULL);

	createWindowClass();
	registerWindowClass();
}

void WindowFactory::destroyWindowClass()
{
	BOOL result = UnregisterClass(WINDOW_CLASS_NAME, _instanceHandle);
	assert(result != FALSE);
}

HWND WindowFactory::createWindow(const int width, const int height) const
{
	DWORD windowStyle = WS_CAPTION | WS_SYSMENU;
	RECT windowRectangle = createWindowRectangle(width, height, windowStyle);

	const int adjustedWidth = windowRectangle.right - windowRectangle.left;
	const int adjustedHeight = windowRectangle.bottom - windowRectangle.top;

	HWND windowHandle = CreateWindowEx(0, WINDOW_CLASS_NAME, WINDOW_TITLE, windowStyle, windowRectangle.left,
		windowRectangle.top, adjustedWidth, adjustedHeight, NULL, NULL, _instanceHandle, NULL);

	assert(windowHandle != NULL);
	initializeInput(windowHandle);

	return windowHandle;
}

void WindowFactory::createWindowClass()
{
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	HICON icon = LoadIcon(NULL, IDI_APPLICATION);

	_windowClass.cbClsExtra = 0;
	_windowClass.cbSize = sizeof(WNDCLASSEX);
	_windowClass.cbWndExtra = 0;
	_windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	_windowClass.hCursor = cursor;
	_windowClass.hIcon = icon;
	_windowClass.hIconSm = icon;
	_windowClass.hInstance = _instanceHandle;
	_windowClass.lpfnWndProc = processMessage;
	_windowClass.lpszClassName = WINDOW_CLASS_NAME;
	_windowClass.lpszMenuName = NULL;
	_windowClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
}

void WindowFactory::registerWindowClass()
{
	ATOM result = RegisterClassEx(&_windowClass);
	assert(result != 0);
}

RECT WindowFactory::createWindowRectangle(const int width, const int height, const DWORD style) const
{
	int halfScreenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
	int halfScreenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;

	RECT rectangle;
	rectangle.left = halfScreenWidth - width / 2;
	rectangle.top = halfScreenHeight - height / 2;
	rectangle.right = rectangle.left + width;
	rectangle.bottom = rectangle.top + height;

	BOOL result = AdjustWindowRect(&rectangle, style, FALSE);
	assert(result != FALSE);

	return rectangle;
}

void WindowFactory::initializeInput(HWND windowHandle) const
{
	RAWINPUTDEVICE inputDevices[2];
	
	inputDevices[0].dwFlags = RIDEV_NOLEGACY;
	inputDevices[0].hwndTarget = windowHandle;
	inputDevices[0].usUsage = 6;
	inputDevices[0].usUsagePage = 1;

	inputDevices[1].dwFlags = 0;
	inputDevices[1].hwndTarget = windowHandle;
	inputDevices[1].usUsage = 2;
	inputDevices[1].usUsagePage = 1;

	BOOL result = RegisterRawInputDevices(inputDevices, 2, sizeof(RAWINPUTDEVICE));
	assert(result != FALSE);
}

// Static

LRESULT CALLBACK WindowFactory::processMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch(message)
	{
		case WM_CLOSE:
			PostMessage(windowHandle, message, wParam, lParam);
			break;

		case WM_INPUT:
			processInput((HRAWINPUT)lParam);
			break;

		case WM_MOUSEMOVE:
			processMouseMovement(lParam);
			break;

		default:
			result = DefWindowProc(windowHandle, message, wParam, lParam);
			break;
	}

	return result;
}

void WindowFactory::processInput(const HRAWINPUT inputDataHandle)
{
	RAWINPUT* inputData = getInputData(inputDataHandle);

	switch(inputData->header.dwType)
	{
		case RIM_TYPEKEYBOARD:
			Input::processKeyboardData(inputData->data.keyboard);
			break;

		case RIM_TYPEMOUSE:
			Input::processMouseData(inputData->data.mouse);
			break;
	}

	delete[] inputData;
}

void WindowFactory::processMouseMovement(const LPARAM coords)
{
	const int x = LOWORD(coords);
	const int y = HIWORD(coords);

	Input::processMouseData(x, y);
}

RAWINPUT* WindowFactory::getInputData(const HRAWINPUT inputDataHandle)
{
	UINT dataSize;
	UINT result = GetRawInputData(inputDataHandle, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

	assert(result != -1);

	BYTE* data = new BYTE[dataSize];
	result = GetRawInputData(inputDataHandle, RID_INPUT, data, &dataSize, sizeof(RAWINPUTHEADER));
	
	assert(result == dataSize);
	return (RAWINPUT*)data;
}

Window* WindowFactory::getWindowPointer(HWND windowHandle)
{
	LONG window = GetWindowLongPtr(windowHandle, GWLP_USERDATA);
	assert(window != 0);

	return (Window*)window;
}