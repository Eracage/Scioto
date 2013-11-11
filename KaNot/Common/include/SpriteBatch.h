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

		void Init();
		
		void Draw(Sprite* sprite, float depth = 0.0f, Vector2 position = Vector2(),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 1);
		void Draw(Vector2* vector2, float depth = 0.0f, Vector2 position = Vector2(),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);
		void Draw(Vector3* vector3, float depth = 0.0f, Vector2 position = Vector2(),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);
		void Draw(Rectangle* rectangle, float depth = 0.0f, Vector2 position = Vector2(),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);

		void Render();

		int addShader(Shader* shader);
		
		
	private:

		void setScale(Vector2 scale);
		void setTranslation(Vector3 position);
		void setRotation(float rotation);

		void genBuffers();

		void Sort();

		void AddDraw(Drawable* drawable);

		std::vector<Shader*> m_shaders;
		Viewport* m_viewport;

		std::vector<Drawable*> m_drawables;

		std::vector<float*> m_datas;
		std::vector<GLuint> VBOs;
		
		float* m_scale;
		float* m_translation;
		float* m_rotation;

		Vector2 m_last_scale;
		Vector3 m_last_position;
		float m_last_rotation;
	};

}
#endif