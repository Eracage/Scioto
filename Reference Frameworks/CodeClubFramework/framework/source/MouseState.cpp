/**
 * @file MouseState.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <MouseState.h>

using namespace devmath;
using namespace glframework;
using namespace std;

MouseState::MouseState()
	: _coords(Point::zero()),
	  _wheel(0) { }

MouseState::MouseState(const Point& coords, const vector<bool>& buttonStates, const int wheel)
	: _coords(coords),
	  _buttonStates(buttonStates),
	  _wheel(wheel) { }

MouseState::MouseState(const MouseState& mouseState)
	: _coords(mouseState._coords),
	  _buttonStates(mouseState._buttonStates),
	  _wheel(mouseState._wheel) { }

MouseState::~MouseState() { }

bool MouseState::leftButton() const
{
	return _buttonStates[0];
}

bool MouseState::middleButton() const
{
	return _buttonStates[1];
}

bool MouseState::rightButton() const
{
	return _buttonStates[2];
}

bool MouseState::x1Button() const
{
	return _buttonStates[3];
}

bool MouseState::x2Button() const
{
	return _buttonStates[4];
}

int MouseState::wheel() const
{
	return _wheel;
}

int MouseState::x() const
{
	return _coords.x;
}

int MouseState::y() const
{
	return _coords.y;
}

MouseState& MouseState::operator =(const MouseState& mouseState)
{
	if(this != &mouseState)
	{
		_coords = mouseState._coords;
		_buttonStates = mouseState._buttonStates;
		_wheel = mouseState._wheel;
	}

	return *this;
}