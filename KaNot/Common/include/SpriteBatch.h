#pragma once
#ifndef SPRITEBATCH_H_SCIOTO
#define SPRITEBATCH_H_SCIOTO

#include "Shader.h"
#include "Viewport.h"
#include <vector>
#include "Drawable.h"

namespace Scioto
{

	class SpriteBatch
	{
	public:
		SpriteBatch(Viewport* viewport);
		~SpriteBatch();

		void Init();
		
		void Draw(Drawable* drawable);
		void Draw(Vector2* vector2,Vector2 position = Vector2(), float depth = 0.0f, Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);
		void Draw(Vector3* vector3,Vector2 position = Vector2(), float depth = 0.0f, Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);
		void Draw(Rectangle* rectangle,Vector2 position = Vector2(), float depth = 0.0f, Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f),
			Vector2 scale = Vector2(1,1),float rotation = 0.0f,int shader = 0);

		void Render();

		int addShader(Shader* shader);
		
		
	private:

		void setScale(Vector2 scale);
		void setTranslation(Vector2 position, float depth);
		void setTranslation(Vector3 position);
		void setRotation(float rotation);

		void genBuffers();

		void Sort();

		void AddDraw(Drawable* drawable);

		std::vector<Shader*> m_shaders;
		Viewport* m_viewport;
		
		std::vector<Drawable*> m_drawables;
		std::vector<Drawable*> m_onceDrawables;

		std::vector<float*> m_datas;
		std::vector<GLuint> VBOs;
		
		Matrix4 m_scale;
		Matrix4 m_translation;
		Matrix4 m_rotation;

		Vector2 m_last_scale;
		Vector3 m_last_position;
		float m_last_rotation;
	};

}
#endif