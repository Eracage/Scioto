/**
 * @file MouseState.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include <vector>
#include <devmath/Point.h>

namespace glframework
{
	class MouseState
	{
	public:

		MouseState();

		MouseState(const devmath::Point& coords, const std::vector<bool>& buttonStates, const int wheel);

		MouseState(const MouseState& mouseState);

		~MouseState();

		bool leftButton() const;

		bool middleButton() const;

		bool rightButton() const;

		bool x1Button() const;

		bool x2Button() const;

		int wheel() const;

		int x() const;

		int y() const;

		MouseState& operator =(const MouseState& mouseState);

	private:

		devmath::Point _coords;
		std::vector<bool> _buttonStates;
		int _wheel;
	};
}

#endif