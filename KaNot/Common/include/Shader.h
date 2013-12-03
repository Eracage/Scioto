#pragma once
#ifndef SHADER_H_SCIOTO
#define SHADER_H_SCIOTO

#include "OpenGL.h"
#include "Debug.h"

namespace Scioto
{
	class Shader
	{
	public:
		Shader(const char VertexShaderCode[], const char FragmentShaderCode[]);
		~Shader();

		GLuint PS,VS;
		GLuint Program;

	private:
		Shader(Shader& shader);

		GLuint loadShader(GLenum shaderType, const char* pSource);
		void CheckForCompileError(const GLenum& shaderType, GLenum& shader);
	
	};
}
#endif