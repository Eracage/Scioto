#pragma once
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "Shader.h"
#include "Viewport.h"
#include <vector>
#include "Drawable.h"

namespace Scioto
{

	class SpriteBatch
	{
	public:
		SpriteBatch(Shader* shader0,Viewport* viewport);
		~SpriteBatch();
		
		void Draw(Sprite* sprite, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 1);
		void Draw(Vector2* vector2, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0);
		void Draw(Vector3* vector3, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0);
		void Draw(Rectangle* rectangle, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0);

		void Render();

		int addShader(Shader* shader);
		
		void genBuffers();
		
	private:
		GLuint VBO;

		std::vector<Shader*> m_shaders;
		Viewport* m_viewport;

		std::vector<Drawable> m_drawables;
		
		float* m_scale;
		float* m_translation;
		float* m_rotation;
		
		float* m_data;
		int m_bufferSize
	};

}
#endif