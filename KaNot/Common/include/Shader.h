#ifndef SHADER_H
#define SHADER_H

#include <OpenGL.h>
#include <Debug.h>

namespace Scioto
{

class Shader
{
public:
	Shader(const char*,const char*);
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