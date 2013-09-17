#pragma once
#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#ifndef ENGINE
#define ENGINE
class Engine
{
	public:
		Engine();
		~Engine();
		void Update();
		void Draw();
		int testiluku;
};
#endif