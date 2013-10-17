#ifndef ENGINE
#define ENGINE

#include <Debug.h>
#include <Shader.h>

#include "FileReader.h"

class Engine
{
	public:
		Engine();
		~Engine();
		void Update();
		void Draw();

		Scioto::Shader* shader;



		//////////////////////////////////////////////////////// TEMP
		
		GLuint PS,VS,Position,Uv,Texture;
		GLint loc,loc2,loc3;
		GLfloat* GlProjection;
		GLfloat* GlTranslation;
		float position;
		float sine;
		Scioto::tgaHeader header;


		//amount of vertices for the object
		unsigned int num_vertices;

		GLfloat* Data;
		
		GLuint VBO, VBO2;
};
#endif