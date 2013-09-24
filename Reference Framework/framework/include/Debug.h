/**
 * @file Debug.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <GL/glew.h>

#ifdef NDEBUG
#define checkGLErrors() (void)0
#else
#define checkGLErrors() Debug::checkGLError(__FILE__, __LINE__)
#endif

namespace glframework
{
	class Debug
	{
	public:

		static void checkGLError(const char* file, const unsigned line);

		static void write(const std::string& message);

	private:

		Debug();
		Debug(const Debug& debug);
		~Debug();

		static void writeGLErrorMessage(const GLenum error, const char* file, const unsigned line);
	};
}

#endif