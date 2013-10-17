/**
 * @file Shader.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Shader.h>
#include <cassert>

#include <Debug.h>

using namespace devmath;
using namespace glframework;
using namespace std;

Shader::Shader(const string& vertexCode, const string& fragmentCode)
	: _program(0),
	  _vertexShader(0),
	  _fragmentShader(0)
{
	create(vertexCode, fragmentCode);
}

Shader::Shader(const Shader& shader)
	: _program(shader._program),
	  _vertexShader(shader._vertexShader),
	  _fragmentShader(shader._fragmentShader) { }

Shader::~Shader()
{
	destroy();
}


// Public

GLuint Shader::program() const
{
	return _program;
}

void Shader::setUniform(const string& name, const Matrix4& matrix) const
{
	GLint location = glGetUniformLocation(_program, name.c_str());
	checkGLErrors();
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements());
	checkGLErrors();
}

void Shader::use() const
{
	glUseProgram(_program);
	checkGLErrors();
}


// Private

void Shader::create(const string& vertexCode, const string& fragmentCode)
{
	createProgram();

	_vertexShader = createShader(GL_VERTEX_SHADER, vertexCode);
	_fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentCode);

	linkProgram();
}

void Shader::destroy()
{
	glDeleteShader(_vertexShader);
	checkGLErrors();
	glDeleteShader(_fragmentShader);
	checkGLErrors();
	glDeleteProgram(_program);
	checkGLErrors();
}

void Shader::createProgram()
{
	_program = glCreateProgram();
	checkGLErrors();

	assert(_program != 0);
}

GLuint Shader::createShader(const GLenum type, const string& code)
{
	GLuint shader = glCreateShader(type);
	checkGLErrors();

	assert(shader != 0);

	compileShader(shader, code.c_str());
	attachShader(shader);

	return shader;
}

void Shader::linkProgram()
{
	glLinkProgram(_program);
	checkGLErrors();

	GLint isLinked = GL_FALSE;
	glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
	checkGLErrors();

	if(isLinked == GL_FALSE)
	{
		writeProgramLog();
		destroy();

		assert(false);
	}
}

void Shader::compileShader(const GLuint shader, const char* code)
{
	glShaderSource(shader, 1, &code, NULL);
	checkGLErrors();
	glCompileShader(shader);
	checkGLErrors();

	GLint isCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	checkGLErrors();

	if(isCompiled == GL_FALSE)
	{
		writeShaderLog(shader);
		destroy();

		assert(false);
	}
}

void Shader::attachShader(const GLuint shader) const
{
	glAttachShader(_program, shader);
	checkGLErrors();
}

void Shader::writeProgramLog() const
{
	GLint logLength = 0;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
	checkGLErrors();

	assert(logLength != 0);

	GLchar* log = new GLchar[logLength];
	glGetProgramInfoLog(_program, logLength, NULL, log);
	checkGLErrors();

	Debug::write(log);
	delete[] log;
}

void Shader::writeShaderLog(const GLuint shader) const
{
	GLint logLength = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	checkGLErrors();

	assert(logLength != 0);

	GLchar* log = new GLchar[logLength];
	glGetShaderInfoLog(shader, logLength, NULL, log);
	checkGLErrors();

	Debug::write(log);
	delete[] log;
}