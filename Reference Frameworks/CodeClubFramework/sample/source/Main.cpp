/**
 * @file Main.cpp
 *
 * OpenGL Framework - Sample
 * 2013
 */

#include <ctime>
#include <Graphics.h>
#include <Window.h>
#include <WindowFactory.h>

#include <Game.h>

using namespace devmath;
using namespace glframework;

typedef clock_t TIME;

const int FRAMERATE = 60;
const int TICK_SKIP = 1000 / FRAMERATE;

void update(const Window* window, Game* game);
TIME getCurrentTime();

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, CHAR* commandLine, int commandShow)
{
	WindowFactory windowFactory;
	
	Window* window = windowFactory.create(1280, 720);
	Graphics* graphics = new Graphics(window);

	Game* game = new Game(window, graphics);
	update(window, game);

	delete game;
	delete graphics;
	delete window;

	return 0;
}

void update(const Window* window, Game* game)
{
	TIME prevTime = getCurrentTime();

	while(window->processMessages())
	{
		TIME currentTime = getCurrentTime();

		if(currentTime - prevTime >= TICK_SKIP)
		{
			game->update(1.0f / FRAMERATE);
			game->render();

			prevTime = currentTime;
		}
	}
}

TIME getCurrentTime()
{
	return clock() / (CLOCKS_PER_SEC / 1000);
}