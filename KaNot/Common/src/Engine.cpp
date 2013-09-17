#include <Engine.h>

Engine::Engine()
{
	testiluku = 5;
}
Engine::~Engine()
{

}
void Engine::Update()
{

}
void Engine::Draw()
{
	glClearColor(1.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}