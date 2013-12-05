#pragma once
#ifndef DRAWABLE_H_SCIOTO
#define DRAWABLE_H_SCIOTO

namespace Scioto
{
	class Drawable;
}

#include "Sciotomath\Math.h"
#include "Shader.h"

namespace Scioto
{

	class Drawable
	{
		enum DrawableType
		{
			External = 0,
			DrawVector2,
			DrawVector3,
			DrawRectangle,
			DrawCount
		};

		union DrawableObject
		{
		public:
			DrawableObject(void* pointer)
				: m_pointer(pointer)
			{}
			void* m_pointer;
			Vector2* m_vector2;
			Vector3* m_vector3;
			Rectangle* m_rectangle;
		};

	public:
		Drawable();
		Drawable(Vector2* pointer, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0, float depth = 0.0f,Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f));
		Drawable(Vector3* pointer, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0, float depth = 0.0f,Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f));
		Drawable(Rectangle* pointer, Vector2 position = Vector2(),Vector2 scale = Vector2(1,1),
			float rotation = 0.0f,int shader = 0, float depth = 0.0f,Vector4 color = Vector4(0.0f,0.5f,0.6f,1.0f));

		~Drawable();

		virtual void Draw(const Shader* shader, const Matrix4 projection, const Matrix4 translation, const Matrix4 rotation, const Matrix4 scale, GLuint VBO);

		Vector2 m_position;
		Vector2 m_scale;
		float m_rotation;
		float m_depth;
		int m_shader;
		Vector4 m_color;

	private:
		DrawableObject m_object;
		DrawableType m_type;
		
		friend class SpriteBatch;
	};

}
#endif