#include <Shader.h>
#include <stdlib.h>

using namespace Scioto;

Shader::Shader(const char VertexShaderCode[], const char FragmentShaderCode[])
{
	
	
    //compile shader codes
    VS = loadShader(GL_VERTEX_SHADER,VertexShaderCode);
    PS = loadShader(GL_FRAGMENT_SHADER,FragmentShaderCode);
	 
    //make the shader program;
    Program = glCreateProgram();
	
    //attach shaders to the program
    glAttachShader(Program,VS);
    glAttachShader(Program,PS);

    //bind position string to attrib at loc 0
    glBindAttribLocation(Program,0,"position");
	glBindAttribLocation(Program,1,"Uv"); 

    //finalize shader
    glLinkProgram(Program);

	Position = glGetAttribLocation(Program,"vPosition");
	Uv = glGetAttribLocation(Program,"vUv");
	loc = glGetUniformLocation(Program, "s_texture");
	loc2 = glGetUniformLocation(Program, "Projection");
	loc3 = glGetUniformLocation(Program, "Translation");
	loc4 = glGetUniformLocation(Program, "Rotation");
	loc5 = glGetUniformLocation(Program, "Scale");
}

Shader::~Shader()
{}

GLuint Shader::loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
	{
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		CheckForCompileError(shaderType, shader);
    }
    return shader;
}

// Private

void Shader::CheckForCompileError(const GLenum& shaderType, GLenum& shader)
{
	GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) 
	{
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen) 
		{
            char* buf = (char*) malloc(infoLen);
            if (buf) 
			{
                glGetShaderInfoLog(shader, infoLen, NULL, buf);

                LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    
                free(buf);
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
}