/**
 * @file KeyboardState.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <KeyboardState.h>

using namespace glframework;
using namespace std;

KeyboardState::KeyboardState() { }

KeyboardState::KeyboardState(const vector<bool>& keyStates)
	: _keyStates(keyStates) { }

KeyboardState::KeyboardState(const KeyboardState& keyboardState)
	: _keyStates(keyboardState._keyStates) { }

KeyboardState::~KeyboardState() { }


// Public

bool KeyboardState::isKeyDown(const Key key)
{
	return _keyStates[key];
}

bool KeyboardState::isKeyUp(const Key key)
{
	return !isKeyDown(key);
}

// Operators

KeyboardState& KeyboardState::operator =(const KeyboardState& keyboardState)
{
	if(this != &keyboardState)
		_keyStates = keyboardState._keyStates;

	return *this;
}