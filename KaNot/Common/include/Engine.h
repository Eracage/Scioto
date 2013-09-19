#ifndef ENGINE
#define ENGINE

#include <Debug.h>
#include <Shader.h>

class Engine
{
	public:
		Engine();
		~Engine();
		void Update();
		void Draw();
		static void printGLString(const char *name, GLenum s);
		static void checkGlError(const char* op);

		Scioto::Shader* shader;
};
#endif