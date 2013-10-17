/**
 * @file BaseGame.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <BaseGame.h>

using namespace glframework;

BaseGame::BaseGame(Window* window, Graphics* graphics)
	: _window(window),
	  _graphics(graphics) { }

BaseGame::~BaseGame() { }


// Public

void BaseGame::render()
{
	_window->swapBuffers();
}