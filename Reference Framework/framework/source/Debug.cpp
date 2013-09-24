/**
 * @file Debug.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Debug.h>

#include <Windows.h>
#include <sstream>

using namespace glframework;
using namespace std;

// Public

// Static

void Debug::checkGLError(const char* file, const unsigned line)
{
	GLenum error = GL_NO_ERROR;

	do
	{
		error = glGetError();

		if(error != GL_NO_ERROR)
			writeGLErrorMessage(error, file, line);
	}
	while(error != GL_NO_ERROR);
}

void Debug::write(const string& message)
{
	string formattedMessage = message + '\n';
	OutputDebugStringA(formattedMessage.c_str());
}


// Private

// Static

void Debug::writeGLErrorMessage(const GLenum error, const char* file, const unsigned line)
{
	wstringstream message;
	message << L"[OpenGL] Error @ " << file << L" line " << line << L": " << error << '\n';

	OutputDebugString(message.str().c_str());
}