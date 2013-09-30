/**
 * @file Shader.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <devmath/Matrix4.h>
#include <GL/glew.h>

namespace glframework
{
	class Shader
	{
	public:
		
		Shader(const std::string& vertexCode, const std::string& fragmentCode);

		Shader(const Shader& shader);

		~Shader();

		GLuint program() const;

		void setUniform(const std::string& name, const devmath::Matrix4& matrix) const;

		void use() const;

	private:

		GLuint _program;
		GLuint _vertexShader;
		GLuint _fragmentShader;

		void create(const std::string& vertexCode, const std::string& fragmentCode);
		void destroy();
		void createProgram();
		GLuint createShader(const GLenum type, const std::string& code);
		void linkProgram();
		void compileShader(const GLuint shader, const char* code);
		void attachShader(const GLuint shader) const;
		void writeProgramLog() const;
		void writeShaderLog(const GLuint shader) const;
	};
}

#endif