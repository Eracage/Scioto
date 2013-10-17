/**
 * @file Input.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <Windows.h>
#include <devmath/Point.h>

#include <KeyboardState.h>
#include <MouseState.h>

namespace glframework
{
	class Input
	{
	public:

		static KeyboardState keyboardState();

		static MouseState mouseState();

		static void processKeyboardData(RAWKEYBOARD& data);

		static void processMouseData(const int x, const int y);

		static void processMouseData(RAWMOUSE& data);

	private:

		static const USHORT EXTENDED_KEYS[];

		static std::vector<bool> _keyStates;

		static devmath::Point _mouseCoords;
		static std::vector<bool> _mouseButtonStates;
		static int _mouseWheel;

		Input(const Input& input);
		~Input();

		static void parseKeyboardData(RAWKEYBOARD& data);
		static void parseMouseButtonState(const int buttonIndex, const USHORT buttonData, const USHORT buttonDownBit, const USHORT buttonUpBit);
		static void parseShiftKey(RAWKEYBOARD& data);
		static void parseExtendedKeys(RAWKEYBOARD& data, const int index);
	};
}

#endif