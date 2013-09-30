#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>

class Engine
{
public:

	Engine();
	~Engine(); 
	void fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);
	void Update();
	void Draw();
	float Scale,blackBarH,blackBarV;

	private:
		GLuint VBO,VBO2,Program,PS,VS,Position,Uv,Texture;
		GLint loc,loc2,loc3;
		GLfloat* GlProjection;
		GLfloat* GlTranslation;
		unsigned int num_vertices;
		GLfloat* Data;
		float position;
		float sine;
};
#endif