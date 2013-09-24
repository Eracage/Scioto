/**
 * @file Input.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Input.h>

using namespace devmath;
using namespace glframework;
using namespace std;

// Public

// Static

KeyboardState Input::keyboardState()
{
	return KeyboardState(_keyStates);
}

MouseState Input::mouseState()
{
	return MouseState(_mouseCoords, _mouseButtonStates, _mouseWheel);
}

void Input::processKeyboardData(RAWKEYBOARD& data)
{
	if(data.VKey == 0xFF)
		return;

	parseKeyboardData(data);
	const USHORT flags = data.Flags;

	if((flags & RI_KEY_BREAK) != 0)
		_keyStates[data.VKey] = false;
	else
		_keyStates[data.VKey] = true;
}

void Input::processMouseData(const int x, const int y)
{
	_mouseCoords = Point(x, y);
}

void Input::processMouseData(RAWMOUSE& data)
{
	const USHORT buttonData = data.usButtonFlags;

	parseMouseButtonState(0, buttonData, RI_MOUSE_LEFT_BUTTON_DOWN, RI_MOUSE_LEFT_BUTTON_UP);
	parseMouseButtonState(1, buttonData, RI_MOUSE_MIDDLE_BUTTON_DOWN, RI_MOUSE_MIDDLE_BUTTON_UP);
	parseMouseButtonState(2, buttonData, RI_MOUSE_RIGHT_BUTTON_DOWN, RI_MOUSE_RIGHT_BUTTON_UP);
	parseMouseButtonState(3, buttonData, RI_MOUSE_BUTTON_4_DOWN, RI_MOUSE_BUTTON_4_UP);
	parseMouseButtonState(4, buttonData, RI_MOUSE_BUTTON_5_DOWN, RI_MOUSE_BUTTON_5_UP);

	_mouseWheel = (short)data.usButtonData;
}


// Private

const USHORT Input::EXTENDED_KEYS[] =
{
	VK_LCONTROL,
	VK_RCONTROL,
	VK_LMENU,
	VK_RMENU
};

vector<bool> Input::_keyStates = vector<bool>(256, false);

Point Input::_mouseCoords = Point::zero();
vector<bool> Input::_mouseButtonStates = vector<bool>(5, false);
int Input::_mouseWheel = 0;

// Static

void Input::parseKeyboardData(RAWKEYBOARD& data)
{
	switch(data.VKey)
	{
		case VK_SHIFT:
			parseShiftKey(data);
			break;

		case VK_CONTROL:
			parseExtendedKeys(data, 0);
			break;

		case VK_MENU:
			parseExtendedKeys(data, 2);
			break;
	}
}

void Input::parseMouseButtonState(const int buttonIndex, const USHORT buttonData, const USHORT buttonDownBit, const USHORT buttonUpBit)
{
	if((buttonData & buttonDownBit) != 0)
		_mouseButtonStates[buttonIndex] = true;
	else if((buttonData & buttonUpBit) != 0)
		_mouseButtonStates[buttonIndex] = false;
}

void Input::parseShiftKey(RAWKEYBOARD& data)
{
	data.VKey = (USHORT)MapVirtualKey(data.MakeCode, MAPVK_VSC_TO_VK_EX);
}

void Input::parseExtendedKeys(RAWKEYBOARD& data, const int index)
{
	if((data.Flags & RI_KEY_E0) != 0)
		data.VKey = EXTENDED_KEYS[index + 1];
	else
		data.VKey = EXTENDED_KEYS[index];
}