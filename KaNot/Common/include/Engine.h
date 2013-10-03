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

		Scioto::Shader* shader;



		//////////////////////////////////////////////////////// TEMP
		//amount of vertices for the object
		unsigned int num_vertices;

		GLfloat* Data;
		
		GLuint VBO;
};
#endif