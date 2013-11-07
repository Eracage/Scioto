#pragma once
#ifndef DRAWABLE_H
#define	DRAWABLE_H
#include "Sprite.h"
#include "Sciotomath\Math.h"

namespace Scioto
{

	class Drawable
	{
		enum DrawableType
		{
			DrawSprite = 0,
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
			Sprite* m_sprite;
			Vector2* m_vector2;
			Vector3* m_vector3;
			Rectangle* m_rectangle;
		};

	public:
		Drawable(Sprite* sprite, Vector2 position,Vector2 scale,
			float rotation,int shader, float depth);
		Drawable(Vector2* sprite, Vector2 position,Vector2 scale,
			float rotation,int shader, float depth);
		Drawable(Vector3* sprite, Vector2 position,Vector2 scale,
			float rotation,int shader, float depth);
		Drawable(Rectangle* sprite, Vector2 position,Vector2 scale,
			float rotation,int shader, float depth);
		~Drawable();

		Vector2 m_position;
		Vector2 m_scale;
		float m_rotation;
		float m_depth;
		int m_shader;

	private:
		DrawableObject m_object;
		DrawableType m_type;
		
		friend class SpriteBatch;
	};

}
#endif