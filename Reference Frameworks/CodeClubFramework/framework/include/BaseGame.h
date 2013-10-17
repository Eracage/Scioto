/**
 * @file BaseGame.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef BASEGAME_H
#define BASEGAME_H

#include <Graphics.h>
#include <Window.h>

namespace glframework
{
	class BaseGame
	{
	public:

		BaseGame(Window* window, Graphics* graphics);

		virtual ~BaseGame();

		virtual void update(const float elapsedTime) = 0;

		virtual void render() = 0;

	protected:

		Window* _window;
		Graphics* _graphics;

	private:

		BaseGame(const BaseGame& game);
	};
}

#endif